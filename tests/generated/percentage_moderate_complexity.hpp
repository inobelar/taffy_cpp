#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_moderate_complexity.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_moderate_complexity") {
    auto taffy = Taffy::New();
    taffy.disable_rounding();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.45f), Auto<Dimension>() };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Percent(0.5f), Auto<Dimension>() };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(200.0f), Auto<Dimension>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width - 200.0f < 0.1); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height - 42.15625f < 0.1); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 42.15625f, size.height
    
    REQUIRE(location.x - 0.0f < 0.1); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y - 0.0f < 0.1); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width - 97.0f < 0.1); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 97.0f, size.width
    REQUIRE(size.height - 26.15625f < 0.1); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 26.15625f, size.height
    
    REQUIRE(location.x - 8.0f < 0.1); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.x
    REQUIRE(location.y - 8.0f < 0.1); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width - 38.414063f < 0.1); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 38.414063f, size.width
    
    REQUIRE(size.height - 6.0f < 0.1); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 6.0f, size.height
    REQUIRE(location.x - 10.078125f < 0.1); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 10.078125f, location.x
    
    REQUIRE(location.y - 10.078125f < 0.1); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 10.078125f, location.y
    
}
