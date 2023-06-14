#!/usr/bin/env python3

# Example of usage:
#
#   $ python3 ./convert_generated_tests.py --input_dir ../taffy/tests/generated/ --output_dir ./tests/generated/
#

import argparse

import pathlib
import os
import shutil

import re

parser = argparse.ArgumentParser(description='Taffy generated tests converter (rust -> c++)')
parser.add_argument('-i', '--input_dir',  type=pathlib.Path)
parser.add_argument('-o', '--output_dir', type=pathlib.Path)

args = parser.parse_args()

input_dir = args.input_dir
output_dir = args.output_dir

# ------------------------------------------------------------------------------

def read_file(file_path):
    file_content = ""

    with open(file_path, 'r') as f:
        file_content = f.read()

    return file_content

def write_file(file_path, content):
    with open(file_path, 'w') as f:
        f.write(content)

def read_file_lines(file_path):
    lines = []

    with open(file_path, 'r') as f:
        lines = f.readlines()

    return lines

# ------------------------------------------------------------------------------

# via: https://stackoverflow.com/a/273227/
def ensure_directory_exists(dir_path):
    pathlib.Path(dir_path).mkdir(parents=True, exist_ok=True)

# via: https://stackoverflow.com/a/185941/
def clear_directory(dir_path):
    for filename in os.listdir(dir_path):
        file_path = os.path.join(dir_path, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))

# ------------------------------------------------------------------------------

def remove_func_trailing_comma_and_add_semicolon(func_name: str, content: str):

    func_name_len = len(func_name)

    start_index_number = 0

    while True:
        found_index = content.find(func_name, start_index_number, len(content))

        if found_index == -1: # not found
            break
        else: # found
            start_index_number = found_index + func_name_len # shift search-start for the next iteration

        # ----------------------------------------------------------------------
        
        brackets_stack = []
        comma_indexes_to_remove = []

        # Helper stack-like functions
        def is_empty(list): return len(list) == 0
        def get_top(list): return list[-1]

        index = found_index

        # ----------------------------------------------------------------------

        # Find first opening bracket '(' index
        while True:
            if content[index] == '(':
                index += 1 # additional step, to not start next from this character
                break
            index += 1

        # ----------------------------------------------------------------------

        while True:
            if content[index] == '(':
                brackets_stack.append('(')
            elif content[index] == '{':
                brackets_stack.append('{')
            elif content[index] == '[':
                brackets_stack.append('[')

            elif content[index] == ')':
                if is_empty(brackets_stack):

                    # ----------------------------------------------------------
                    # Additional traversing for inserting ';' after function 
                    # call, if it's needed
                    for i in range(index+1, len(content)):
                        if content[i] == ' ' or content[i] == '\n':
                            continue
                        else:
                            if content[i] == ')' or content[i] == '}':

                                content_mutable = list(content)
                                content_mutable.insert(index+1, ';')
                                content = ''.join(content_mutable)

                                break
                            else: # content[i] != ')' and != '}'
                                break
                    # ----------------------------------------------------------


                    break
                else:
                    if get_top(brackets_stack) == '(':
                        brackets_stack.pop()
                    else:
                        raise Exception('Wrong brackets pairs: found bracket ")", but previous bracket is not "(')
            elif content[index] == '}':
                if is_empty(brackets_stack):
                    raise Exception('Wrong brackets pairs: found bracket "}", but previous bracket "{" not exists')
                else:
                    if get_top(brackets_stack) == '{':
                        brackets_stack.pop()
                    else: 
                        raise Exception('Wrong brackets pairs: found bracket "}", but previous bracket is not "{"')
            elif content[index] == ']':
                if is_empty(brackets_stack):
                    raise Exception('Wrong brackets pairs: found bracket "]", but previous bracket "[" not exists')
                else:
                    if get_top(brackets_stack) == '[':
                        brackets_stack.pop()
                    else: 
                        raise Exception('Wrong brackets pairs: found bracket "]", but previous bracket is not "["')


            elif content[index] == ',':
                if is_empty(brackets_stack): # if that comma not in nested brackets --> between topmost '(' and ')'

                    for i in range(index+1, len(content)):
                        if content[i] == ' ' or content[i] == '\n':
                            continue
                        else: # content[i] != ' ' and != '\n'
                            if content[i] == ')':
                                comma_indexes_to_remove.append(index)
                            break

            index += 1

        if not is_empty(comma_indexes_to_remove):
            content_mutable = list(content) # 'str' --> 'list', since 'str' is immutable

            for i in comma_indexes_to_remove:
                # content_mutable[i] = '@' # <-- for debug
                del content_mutable[i] 

            content = ''.join(content_mutable)  # 'list' --> 'str'

    return content

# ------------------------------------------------------------------------------

def replace_float(match):
    if '.' in match.group(2):
        return match.group(2) + 'f'
    else:
        return match.group(2) + '.0f'

# property : 42, --> property = 42;
def replace_property_Float(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*(\S+)\s*,',
        output_var_name + r' = \1;',
        content)

# property : Some ( 42 ), --> property = Some(42);
def replace_property_Option_Float(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*Some\s*\((\S+)\)\s*,',
        output_var_name + r' = Some(\1);',
        content)

# property : Some ( taffy :: style :: AlignItems :: Enum ), --> property = Some(AlignItems::Enum);
def replace_property_Option_AlignItems(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + '\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*AlignItems\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(AlignItems::\1);',
        content)

# property : Some ( taffy :: style :: AlignSelf :: Enum ), --> property = Some(AlignSelf::Enum);
def replace_property_Option_AlignSelf(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + '\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*AlignSelf\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(AlignSelf::\1);',
        content)

# property : Some ( taffy :: style :: AlignContent :: Enum ), --> property = Some(AlignContent::Enum);
def replace_property_Option_AlignContent(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*AlignContent\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(AlignContent::\1);',
        content)

# property : Some ( taffy :: style :: JustifyContent :: Enum ), --> property = Some(JustifyContent::Enum);
def replace_property_Option_JustifyContent(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*JustifyContent\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(JustifyContent::\1);',
        content)

# property : Some ( taffy :: style :: JustifySelf :: Enum ), --> property = Some(JustifySelf::Enum);
def replace_property_Option_JustifySelf(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*JustifySelf\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(JustifySelf::\1);',
        content)

# property : Some ( taffy :: style :: JustifyItems :: Enum ), --> property = Some(JustifyItems::Enum);
def replace_property_Option_JustifyItems(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*Some\s*\(\s*taffy\s*::\s*style\s*::\s*JustifyItems\s*::\s*(\S+)\s*\)\s*,',
        output_var_name + r' = Some(JustifyItems::\1);',
        content)

# property : taffy :: style :: FlexDirection :: Enum , --> property = FlexDirection::Enum;
def replace_property_FlexDirection(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + '\s*:\s*taffy\s*::\s*style\s*::\s*FlexDirection\s*::\s*(Row|Column|RowReverse|ColumnReverse)\s*,',
        output_var_name + r' = FlexDirection::\1();',
        content)

# property : taffy :: style :: FlexWrap :: Enum , --> property = FlexWrap::Enum;
def replace_property_FlexWrap(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + '\s*:\s*taffy\s*::\s*style\s*::\s*FlexWrap\s*::\s*(NoWrap|Wrap|WrapReverse)\s*,',
        output_var_name + r' = FlexWrap::\1();',
        content)

# property : taffy :: style :: GridAutoFlow :: Enum , --> property = GridAutoFlow::Enum();
def replace_property_GridAutoFlow(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*taffy\s*::\s*style\s*::\s*GridAutoFlow\s*::\s*(Row|Column|RowDense|ColumnDense)\s*,',
        output_var_name + r' = GridAutoFlow::\1();',
        content)

# property : taffy :: style :: Display :: Enum , --> property = Display::Enum();
def replace_property_Display(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*taffy\s*::\s*style\s*::\s*Display\s*::\s*(Flex|Grid|Block|None)\s*,',
        output_var_name + r' = Display::\1();',
        content)

# property : taffy :: style :: Position :: Enum , --> property = Position::Enum();
def replace_property_Position(search_var_name, output_var_name, content):
    return re.sub(
        search_var_name + r'\s*:\s*taffy\s*::\s*style\s*::\s*Position\s*::\s*(Relative|Absolute)\s*,',
        output_var_name + r' = Position::\1();',
        content)

def replace_property_Dimension(search_var_name, output_var_name, content):
    content = re.sub(
        search_var_name + r'\s*:\s*taffy\s*::\s*style\s*::\s*Dimension\s*::\s*(Length|Percent)\s*\((\S+)\)\s*,',
        output_var_name + r' = Dimension::\1(\2);',
        content)

    # TODO: possibly this case never exists
    content = re.sub(
        search_var_name + r'\s*:\s*taffy\s*::\s*style\s*::\s*Dimension\s*::\s*Auto\s*,',
        output_var_name + r' = Dimension::Auto();',
        content)

    content = re.sub(
        search_var_name + r'\s*:\s*auto\s*\(\)\s*,',
        output_var_name + r' = Auto<Dimension>();',
        content)

    return content

def replace_property_Point_Overflow(search_var_name, output_var_name, content):

    # TODO: test here, that 'x' before 'y' (right order)

    def replace(matched):
        point_content = matched.group(1)

        point_content = re.sub(
            r'(x|y)\s*:\s*taffy\s*::\s*style\s*::\s*Overflow\s*::\s*(Visible|Hidden|Scroll)',
            r'Overflow::\2()',
            point_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in point_content.split(','))
        items = [item for item in items_stripped if item]
        point_content = ', '.join(items)

        return output_var_name + r' = Point<Overflow> { ' + point_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Point\s*\{([^\}]+)}\s*,', replace, content)

def replace_property_Size_Dimension(search_var_name, output_var_name, content):

    # TODO: test here, that 'width' before 'height' (right order)

    def replace(matched):
        size_content = matched.group(1)

        size_content = re.sub(
            r'(width|height)\s*:\s*taffy\s*::\s*style\s*::\s*Dimension\s*::\s*(Length|Percent)\s*\((\S+)\)',
            r'Dimension::\2(\3)',
            size_content)

        # TODO: possibly this case never exists
        size_content = re.sub(
            r'(width|height)\s*:\s*taffy\s*::\s*style\s*::\s*Dimension\s*::\s*Auto',
            r'Dimension::Auto()',
            size_content)

        size_content = re.sub(
            r'(width|height)\s*:\s*auto\s*\(\)',
            r'Auto<Dimension>()',
            size_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in size_content.split(','))
        items = [item for item in items_stripped if item]
        size_content = ', '.join(items)

        return output_var_name + r' = Size<Dimension> { ' + size_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Size\s*\{([^\}]+)}\s*,', replace, content)

def replace_property_Size_LengthPercentage(search_var_name, output_var_name, content):

    # TODO: test here, that 'width' before 'height' (right order)

    def replace(matched):
        size_content = matched.group(1)

        size_content = re.sub(
            r'(width|height)\s*:\s*taffy\s*::\s*style\s*::\s*LengthPercentage\s*::\s*(Length|Percent)\s*\((\S+)\)',
            r'LengthPercentage::\2(\3)',
            size_content)

        size_content = re.sub(
            r'(width|height)\s*:\s*auto\s*\(\)',
            r'Auto<LengthPercentage>()',
            size_content)

        size_content = re.sub(
            r'(width|height)\s*:\s*zero\s*\(\)',
            r'zero<LengthPercentage>()',
            size_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in size_content.split(','))
        items = [item for item in items_stripped if item]
        size_content = ', '.join(items)

        return output_var_name + r' = Size<LengthPercentage> { ' + size_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Size\s*\{([^\}]+)}\s*,', replace, content)

def replace_property_Line_GridPlacement(search_var_name, output_var_name, content):

    # TODO: test here, that 'start' before 'end' (right order)

    def replace(matched):
        line_content = matched.group(1)

        line_content = re.sub(
            r'(start|end)\s*:\s*line\s*\((\S+)\)',
            r'line<GridPlacement>(\2)',
            line_content)

        line_content = re.sub(
            r'(start|end)\s*:\s*taffy\s*::\s*style\s*::\s*GridPlacement\s*::\s*Auto',
            r'GridPlacement::Auto()',
            line_content)

        line_content = re.sub(
            r'(start|end)\s*:\s*taffy\s*::\s*style\s*::\s*GridPlacement\s*::\s*(Line|Span)\s*\((\S+)\)',
            r'GridPlacement::\2(\3)',
            line_content)

        # line_content = re.sub(
        #     r'(start|end)\s*:\s*auto\s*\(\)',
        #     r'Auto<Dimension>()',
        #     line_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in line_content.split(','))
        items = [item for item in items_stripped if item]
        line_content = ', '.join(items)

        return output_var_name + r' = Line<GridPlacement> { ' + line_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Line\s*\{([^\}]+)}\s*,', replace, content)

def replace_property_Rect_LengthPercentage(search_var_name, output_var_name, content):

    # TODO: test here that order the next: [left,right,top,bottom]

    def replace(matched):
        rect_content = matched.group(1)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*taffy\s*::\s*style\s*::\s*LengthPercentage\s*::\s*(Length|Percent)\s*\((\S+)\)',
            r'LengthPercentage::\2(\3)',
            rect_content)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*auto\s*\(\)',
            r'Auto<LengthPercentage>()',
            rect_content)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*zero\s*\(\)',
            r'zero<LengthPercentage>()',
            rect_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in rect_content.split(','))
        items = [item for item in items_stripped if item]
        rect_content = ', '.join(items)

        return output_var_name + r' = Rect<LengthPercentage> { ' + rect_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Rect\s*\{([^\}]+)},', replace, content, flags=re.MULTILINE)

def replace_property_Rect_LengthPercentageAuto(search_var_name, output_var_name, content):

    # TODO: test here that order the next: [left,right,top,bottom]

    def replace(matched):
        rect_content = matched.group(1)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*taffy\s*::\s*style\s*::\s*LengthPercentageAuto\s*::\s*(Length|Percent)\s*\((\S+)\)',
            r'LengthPercentageAuto::\2(\3)',
            rect_content)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*taffy\s*::\s*style\s*::\s*LengthPercentageAuto\s*::\s*Auto',
            r'LengthPercentageAuto::Auto()',
            rect_content)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*auto\s*\(\)',
            r'Auto<LengthPercentageAuto>()',
            rect_content)

        rect_content = re.sub(
            r'(left|right|top|bottom)\s*:\s*zero\s*\(\)',
            r'zero<LengthPercentageAuto>()',
            rect_content)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        items_stripped = (item.strip() for item in rect_content.split(','))
        items = [item for item in items_stripped if item]
        rect_content = ', '.join(items)

        return output_var_name + r' = Rect<LengthPercentageAuto> { ' + rect_content + ' };'

    return re.sub(search_var_name + r'\s*:\s*taffy\s*::\s*geometry\s*::\s*Rect\s*\{([^\}]+)},', replace, content, flags=re.MULTILINE)

def replace_property_GridTrackVec_TrackSizingFunction(search_var_name, output_var_name, content):

    content = re.sub(
        # repeat(GridTrackRepetition::AutoFill, vec![length(???)])
        r'repeat\s*\(\s*GridTrackRepetition\s*::\s*(AutoFit|AutoFill)\s*,\s*vec\!\s*\[\s*length\s*\((\S+)\)\s*\]\s*\)',
        r'repeat(GridTrackRepetition::\1(), Vec<NonRepeatedTrackSizingFunction>{ length<NonRepeatedTrackSizingFunction>(\2) } )',
        content)

    content = re.sub(
        # repeat(GridTrackRepetition::Count(???), vec![length(???)]),
        r'repeat\s*\(\s*GridTrackRepetition\s*::\s*Count\((\S+)\)\s*,\s*vec\!\s*\[\s*length\s*\((\S+)\)\s*\]\s*\)',
        r'repeat(GridTrackRepetition::Count(\1), Vec<NonRepeatedTrackSizingFunction>{ length<NonRepeatedTrackSizingFunction>(\2) } )',
        content)


    def replace(matched):
        vec_content = matched.group(1)

        # ----------------------------------------------------------------------
        # length() first

        # minmax( length(???), length(???) )
        vec_content = re.sub(
            r'minmax\s*\(\s*length\s*\((\S+)\),\s*length\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(\1), length<MaxTrackSizingFunction>(\2))',
            vec_content)
        
        # minmax( length(???), (min|max)_content() )
        vec_content = re.sub(
            r'minmax\s*\(\s*length\s*\((\S+)\),\s*min_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(\1), min_content<MaxTrackSizingFunction>())',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*length\s*\((\S+)\),\s*max_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(\1), max_content<MaxTrackSizingFunction>())',
            vec_content)

        # minmax( length(???), auto() )
        vec_content = re.sub(
            r'minmax\s*\(\s*length\s*\((\S+)\),\s*auto\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(\1), Auto<MaxTrackSizingFunction>())',
            vec_content)

        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        # auto() first
        
        # minmax( auto(), length|percent() )
        vec_content = re.sub(
            r'minmax\s*\(\s*auto\s*\(\),\s*length\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(Auto<MinTrackSizingFunction>(), length<MaxTrackSizingFunction>(\1))',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*auto\s*\(\),\s*percent\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(Auto<MinTrackSizingFunction>(), percent<MaxTrackSizingFunction>(\1))',
            vec_content)

        # minmax( auto(), (min|max)_content() )
        vec_content = re.sub(
            r'minmax\s*\(\s*auto\s*\(\),\s*min_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(Auto<MinTrackSizingFunction>(), min_content<MaxTrackSizingFunction>())',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*auto\s*\(\),\s*max_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(Auto<MinTrackSizingFunction>(), max_content<MaxTrackSizingFunction>())',
            vec_content)

        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        # max_content() first

        # minmax( max_content(), fr(???)|auto() )
        vec_content = re.sub(
            r'minmax\s*\(\s*max_content\s*\(\),\s*fr\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), fr<MaxTrackSizingFunction>(\1))',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*max_content\s*\(\),\s*auto\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), Auto<MaxTrackSizingFunction>())',
            vec_content)

        # minmax( max_content(), length|percent(???) )
        vec_content = re.sub(
            r'minmax\s*\(\s*max_content\s*\(\),\s*length\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), length<MaxTrackSizingFunction>(\1))',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*max_content\s*\(\),\s*percent\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), percent<MaxTrackSizingFunction>(\1))',
            vec_content)

        # minmax( max_content(), min_content() )
        vec_content = re.sub(
            r'minmax\s*\(\s*max_content\s*\(\),\s*min_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), min_content<MaxTrackSizingFunction>())',
            vec_content)

        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        # min_content() first

        # minmax( min_content(), fr(???)|auto )
        vec_content = re.sub(
            r'minmax\s*\(\s*min_content\s*\(\),\s*fr\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), fr<MaxTrackSizingFunction>(\1))',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*min_content\s*\(\),\s*auto\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), Auto<MaxTrackSizingFunction>())',
            vec_content)

        # minmax( min_content(), length|percent(???) )
        vec_content = re.sub(
            r'minmax\s*\(\s*min_content\s*\(\),\s*length\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), length<MaxTrackSizingFunction>(\1))',
            vec_content)
        vec_content = re.sub(
            r'minmax\s*\(\s*min_content\s*\(\),\s*percent\s*\((\S+)\)\s*\)',
            r'minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), percent<MaxTrackSizingFunction>(\1))',
            vec_content)

        # minmax( min_content(), max_content() )
        vec_content = re.sub(
            r'minmax\s*\(\s*min_content\s*\(\),\s*max_content\s*\(\)\s*\)',
            r'minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), max_content<MaxTrackSizingFunction>())',
            vec_content)

        # ----------------------------------------------------------------------

        vec_content = re.sub(
            r'fit_content\s*\(\s*percent\s*\((\S+)\)\s*\)',
            r'fit_content<TrackSizingFunction>(percent<LengthPercentage>(\1))',
            vec_content)
        vec_content = re.sub(
            r'fit_content\s*\(\s*length\s*\((\S+)\)\s*\)',
            r'fit_content<TrackSizingFunction>(length<LengthPercentage>(\1))',
            vec_content)


        vec_content = re.sub(
            r'length\s*\((\S+)\)',
            r'length<TrackSizingFunction>(\1)',
            vec_content)

        vec_content = re.sub(
            r'percent\s*\((\S+)\)',
            r'percent<TrackSizingFunction>(\1)',
            vec_content)

        vec_content = re.sub(
            r'fr\s*\((\S+)\)',
            r'fr<TrackSizingFunction>(\1)',
            vec_content)

        vec_content = re.sub(
            r'min_content\s*\(\)',
            r'min_content<TrackSizingFunction>()',
            vec_content)

        vec_content = re.sub(
            r'max_content\s*\(\)',
            r'max_content<TrackSizingFunction>()',
            vec_content)

        vec_content = re.sub(
            r'auto\s*\(\)',
            r'Auto<TrackSizingFunction>()',
            vec_content)

        return output_var_name + r' = GridTrackVec<TrackSizingFunction> { ' + vec_content + ' };'

    return re.sub(
        search_var_name + r'\s*:\s*vec\!\[([^\]]+)\]\s*,', 
        replace, 
        content)

def replace_property_GridTrackVec_NonRepeatedTrackSizingFunction(search_var_name, output_var_name, content):

    def replace(matched):
        vec_content = matched.group(1)

        # In tests currently only one this case
        vec_content = re.sub(
            r'length\s*\((\S+)\)',
            r'length<NonRepeatedTrackSizingFunction>(\1)',
            vec_content)

        return output_var_name + r' = GridTrackVec<NonRepeatedTrackSizingFunction> { ' + vec_content + ' };'

    return re.sub(
        search_var_name + r'\s*:\s*vec\!\[([^\]]+)\]\s*,', 
        replace, 
        content)


def replace_style_builder(match):
    content = match.group(2)

    # Display display
    content = replace_property_Display('display', 's.display', content)

    # Point<Overflow> overflow
    content = replace_property_Point_Overflow('overflow', 's.overflow', content)

    # float scrollbar_width
    content = replace_property_Float('scrollbar_width', 's.scrollbar_width', content)

    # Position position
    content = replace_property_Position('position', 's.position', content)

    # Rect<LengthPercentageAuto> inset
    content = replace_property_Rect_LengthPercentageAuto('inset', 's.inset', content)

    # Size<Dimension> min_size
    content = replace_property_Size_Dimension('min_size', 's.min_size', content)

    # Size<Dimension> max_size
    content = replace_property_Size_Dimension('max_size', 's.max_size', content)

    # Size<Dimension> size
    content = replace_property_Size_Dimension('size', 's.size', content) # NOTE: Must be afer 'min_size' and 'max_size' to not replace them & not corrupt everything

    # Option<float> aspect_ratio
    content = replace_property_Option_Float('aspect_ratio', 's.aspect_ratio', content)

    # Rect<LengthPercentageAuto> margin
    content = replace_property_Rect_LengthPercentageAuto('margin', 's.margin', content)

    # Rect<LengthPercentage> padding
    content = replace_property_Rect_LengthPercentage('padding', 's.padding', content)

    # Rect<LengthPercentage> border
    content = replace_property_Rect_LengthPercentage('border', 's.border', content)

    # Option<AlignItems> align_items
    content = replace_property_Option_AlignItems('align_items', 's.align_items', content)

    # Option<AlignSelf> align_self
    content = replace_property_Option_AlignSelf('align_self', 's.align_self', content)

    # Option<AlignItems> justify_items
    content = replace_property_Option_JustifyItems('justify_items', 's.justify_items', content)

    # Option<AlignSelf> justify_self
    content = replace_property_Option_JustifySelf('justify_self', 's.justify_self', content)

    # Option<AlignContent> align_content
    content = replace_property_Option_AlignContent('align_content', 's.align_content', content)

    # Option<JustifyContent> justify_content
    content = replace_property_Option_JustifyContent('justify_content', 's.justify_content', content)

    # Size<LengthPercentage> gap
    content = replace_property_Size_LengthPercentage('gap', 's.gap', content)

    # FlexDirection flex_direction
    content = replace_property_FlexDirection('flex_direction', 's.flex_direction', content)

    # FlexWrap flex_wrap
    content = replace_property_FlexWrap('flex_wrap', 's.flex_wrap', content)

    # Dimension flex_basis
    content = replace_property_Dimension('flex_basis', 's.flex_basis', content)

    # float flex_grow
    content = replace_property_Float('flex_grow', 's.flex_grow', content)

    # float flex_shrink
    content = replace_property_Float('flex_shrink', 's.flex_shrink', content)

    # GridTrackVec<TrackSizingFunction> grid_template_rows
    content = replace_property_GridTrackVec_TrackSizingFunction('grid_template_rows', 's.grid_template_rows', content)

    # GridTrackVec<TrackSizingFunction> grid_template_columns
    content = replace_property_GridTrackVec_TrackSizingFunction('grid_template_columns', 's.grid_template_columns', content)

    # GridTrackVec<NonRepeatedTrackSizingFunction> grid_auto_rows
    content = replace_property_GridTrackVec_NonRepeatedTrackSizingFunction('grid_auto_rows', 's.grid_auto_rows', content)

    # GridTrackVec<NonRepeatedTrackSizingFunction> grid_auto_columns
    content = replace_property_GridTrackVec_NonRepeatedTrackSizingFunction('grid_auto_columns', 's.grid_auto_columns', content)

    # GridAutoFlow grid_auto_flow
    content = replace_property_GridAutoFlow('grid_auto_flow', 's.grid_auto_flow', content)

    # Line<GridPlacement> grid_row
    content = replace_property_Line_GridPlacement('grid_row', 's.grid_row', content)

    # Line<GridPlacement> grid_column
    content = replace_property_Line_GridPlacement('grid_column', 's.grid_column', content)

    # --------------------------------------------------------------------------

    content_empty : bool = content.strip() == ""

    if content_empty :
        return r'StyleBuilder([&](Style&) {' + content + r'})' # Remove 's', so it not produce warning about unused argument
    else:
        return r'StyleBuilder([&](Style& s) {' + content + r'})'


def replace_unicode(match):
    content = match.group(1)

    # \u{200b} --> \u200b
    content = re.sub(
        r'\\u\{200b\}',
        r'\\u200b',
        content)

    # \u{a0} --> \xa0
    content = re.sub(
        r'\\u\{a0\}',
        r'\\xa0',
        content)

    return r'const char16_t* TEXT = u"' + content + r'";'

def replace_slice(match):
    content = match.group(1)

    # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
    # via: https://stackoverflow.com/a/28534179/
    items_stripped = (item.strip() for item in content.split(','))
    items = [item for item in items_stripped if item]
    content = ', '.join(items)

    return r'mkVec(' + content + ')'

# Replaces:
#   assert_eq!(location.x, 0.0f, "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x);
# with:
#   REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x)
def replace_assert_eq(content: str) -> str:

    def replace(matched) -> str:
        var_a : str              = matched.group(1)
        var_b : str              = matched.group(2)
        message_format_str : str = matched.group(3)
        message_params_str : str = matched.group(4)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        params_stripped = (item.strip() for item in message_params_str.split(','))
        params = [item for item in params_stripped if item]

        message_parts : List(str) = re.split(r'({:\?}|{})', message_format_str)

        param_idx : int = 0
        for i, part in enumerate(message_parts):
            if message_parts[i] == '{:?}':
                message_parts[i] = 'Debug(' + params[param_idx] + ')'
                param_idx += 1
            elif message_parts[i] == '{}':
                message_parts[i] = params[param_idx]
                param_idx += 1
            else:
                if message_parts[i].startswith('"') == False:
                    message_parts[i] = '"' + message_parts[i]
                if message_parts[i].endswith('"') == False:
                    message_parts[i] = message_parts[i] + '"'

        message_parts = list(filter(lambda part : part != '"', message_parts)) # Remove trailing '"'
        message = ', '.join(message_parts)

        return 'REQUIRE_MESSAGE(' + var_a + ' == ' + var_b + ', ' + message + ');'

    return re.sub(
        r'assert_eq!\(([^,]+),\s*([^,]+),\s*(\"[^\"]+\"),\s*([^\)]+)\);',
        replace,
        content)

# Replaces:
#   assert!(size.width - 200f32 < 0.1, "width of node {:?}. Expected {}. Actual {}", node, 200f32, size.width);
# with:
#   REQUIRE_MESSAGE(size.width - 200f32 < 0.1, "width of node ", Debug(node), ". Expected ", 200f32, ". Actual ", size.width);
def replace_assert(content: str) -> str:

    def replace(matched) -> str:
        expression : str         = matched.group(1)
        message_format_str : str = matched.group(2)
        message_params_str : str = matched.group(3)

        # Remove trailing comma: 1) split by ',' 2) trim 3) remove empty 4) join by ', '
        # via: https://stackoverflow.com/a/28534179/
        params_stripped = (item.strip() for item in message_params_str.split(','))
        params = [item for item in params_stripped if item]

        message_parts : List(str) = re.split(r'({:\?}|{})', message_format_str)

        param_idx : int = 0
        for i, part in enumerate(message_parts):
            if message_parts[i] == '{:?}':
                message_parts[i] = 'Debug(' + params[param_idx] + ')'
                param_idx += 1
            elif message_parts[i] == '{}':
                message_parts[i] = params[param_idx]
                param_idx += 1
            else:
                if message_parts[i].startswith('"') == False:
                    message_parts[i] = '"' + message_parts[i]
                if message_parts[i].endswith('"') == False:
                    message_parts[i] = message_parts[i] + '"'

        message_parts = list(filter(lambda part : part != '"', message_parts)) # Remove trailing '"'
        message = ', '.join(message_parts)

        return 'REQUIRE_MESSAGE(' + expression + ', ' + message + ');'

    return re.sub(
        r'assert!\(([^,]+),\s*(\"[^\"]+\"),\s*([^\)]+)\);',
        replace,
        content)

def convert_test_content(file_content):

    # fn test_name() { --> TEST_CASE("test_name") {
    file_content = re.sub(r'(fn (\w+)\(\)) {', r'TEST_CASE("\2") {', file_content)

    # --------------------------------------------------------------------------

    file_content = re.sub(r'\#\[test\]\n', '', file_content)
    file_content = re.sub(r'^\s+\#\[allow\(\w+\)\]\n', '', file_content, flags=re.MULTILINE)
    file_content = re.sub(r'^\s+use taffy::\{prelude::\*, tree::Layout\};\n', '', file_content, flags=re.MULTILINE)

    file_content = re.sub(r'let mut', 'auto', file_content)
    file_content = re.sub(r'let', 'const auto', file_content)

    # --------------------------------------------------------------------------

    # 0f32 --> 0.0f
    # 42f32 --> 42.0f
    # 0.6f32 --> 0.6f
    file_content = re.sub(r'(([\d.]+)f32)', replace_float, file_content)

    # 2u16 --> 2 // TODO: make it: uint16_t{2}
    file_content = re.sub(r'(\d*)u16', r'\1', file_content)
    # 2i16 --> 2 // TODO: make it: int16_t{2}
    file_content = re.sub(r'(\d*)i16', r'\1', file_content)

    # --------------------------------------------------------------------------

    # &[node0, node1] --> mkVec(node0, node1)
    file_content = re.sub(
        r'\&\[([^\]]+)\]', 
        replace_slice, 
        file_content)

    # println!() --> puts("")
    file_content = re.sub(r'println!\(\)', r'puts("")', file_content)
    # println!("\nComputed tree:") --> puts("\nComputed tree:")
    file_content = re.sub(r'println!\((\"[^\"]+\")\)', r'puts(\1)', file_content)

    file_content = replace_assert_eq(file_content)
    file_content = replace_assert(file_content)

    # in 'regex101' it requires '/Ug' - g:global + U:Ungreedy for lazy evaluation.
    file_content = re.sub(
        r'(taffy\s*::\s*style\s*::\s*Style\s*\{)([\s\S]+?)(\s*\.\.\s*Default\s*::\s*default\s*\(\)\s*\})',
        replace_style_builder,
        file_content)

    file_content = re.sub(
        r'const\s*TEXT\s*:\s*\&\s*str\s*=\s*\"([^\"]+)\"\s*\;', 
        replace_unicode, 
        file_content)

    file_content = re.sub(
        r'taffy\s*::\s*tree\s*::\s*MeasureFunc\s*::\s*Raw\s*\(\s*\|\s*known_dimensions\s*,\s*available_space\s*\|',
        r'MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space)',
        file_content)

    file_content = re.sub(
        r'super\s*::\s*WritingMode',
        r'WritingMode',
        file_content)

    file_content = re.sub(
        r'super\s*::\s*measure_standard_text',
        r'return measure_standard_text',
        file_content)


    file_content = re.sub(
        r'compute_layout\(node, taffy::geometry::Size::MAX_CONTENT\)',
        r'compute_layout(node, Size<AvailableSpace>::MAX_CONTENT())',
        file_content)

    # simply to convert &taffy --> taffy (witout ampersand)
    file_content = re.sub(
        r'taffy::util::print_tree\(&taffy, node\)',
        r'print_tree(taffy, node)',
        file_content)

    file_content = re.sub(
        r'const auto Layout { size, location, \.\. } = taffy\.layout\((\S+)\)\.unwrap\(\);',
        r'{ const Layout& l = taffy.layout(\1).unwrap().get(); size = l.size; location = l.location; }',
        file_content
    )

    file_content = re.sub(
        r'taffy::Taffy::new\(\)', 
        r'Taffy::New()', 
        file_content)

    try:
        file_content = remove_func_trailing_comma_and_add_semicolon('new_with_children',     file_content)
        file_content = remove_func_trailing_comma_and_add_semicolon('new_leaf_with_measure', file_content)
        file_content = remove_func_trailing_comma_and_add_semicolon('measure_standard_text', file_content)
    except Exception as e:
        print(e)
        print(file_path)
        print(file_content)
        exit(1)

    return file_content

# ------------------------------------------------------------------------------

# Make sure, that output directory exists (create it, if needed)
ensure_directory_exists(output_dir)
# Make sure, that output directory is empty (erase previously-generated files)
clear_directory(output_dir)

# via: https://stackoverflow.com/a/3207973/
for file_name in os.listdir(input_dir):

    file_path = os.path.join(input_dir, file_name)

    if not os.path.isfile(file_path):
        continue

    if file_name == 'mod.rs':
        continue

    file_content = read_file(file_path)

    file_content = convert_test_content(file_content)

    file_content = \
        '#pragma once\n' + \
        '\n' + \
        '// ATTENTION: GENERATED FROM: taffy/tests/generated/' + file_name + ' ! DO NOT EDIT BY HAND !\n' + \
        '\n' + \
        file_content

    print("Converted {}".format(file_name))
    #print(file_content)

    # Filename without extension
    file_name_without_ext = os.path.splitext(file_name)[0]
    header_file_path = os.path.join(output_dir, file_name_without_ext + '.hpp')
    write_file(header_file_path, file_content)

# ------------------------------------------------------------------------------
# Gather all tests from 'mod.rs'

includes = []
lines = read_file_lines( os.path.join(input_dir, 'mod.rs') )

for idx, line in enumerate(lines):

    matched = re.search(r'mod (\S+);', line)

    if matched:
        name = matched.group(1)

        # Only grid, if previous line have special macro
        is_only_grid = r'#[cfg(feature = "grid")]' in lines[idx-1]

        include = {'is_only_grid': is_only_grid, 'name': name}
        # print(include)

        includes.append(include)

# ------------------------------------------------------------------------------
# Dump gathered tests into 'all_generated_tests.hpp'

with open(os.path.join(output_dir, 'all_generated_tests.hpp'), 'w') as f:

    f.write('#pragma once\n')
    f.write('\n')
    f.write('// ATTENTION: GENERATED FROM: taffy/tests/generated/mod.rs ! DO NOT EDIT BY HAND!\n')
    f.write('\n')

    for include in includes:
        if include['is_only_grid']:
            f.write('#if defined(TAFFY_FEATURE_GRID)\n')
            f.write('  #include "' + include['name'] + '.hpp"\n')
            f.write('#endif // TAFFY_FEATURE_GRID\n')
        else:
            f.write('#include "' + include['name'] + '.hpp"\n')
