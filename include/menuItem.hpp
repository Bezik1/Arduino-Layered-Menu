#pragma once

/**
 * @brief Contains menu data model and navigation. Whole menu tree is
 * evaluated at the compilation time, so it has no runtime overhead.
 *
 */
namespace menu {
enum class MenuItemID
{
    Menu,
    LedOptions,
    Power,
    Red,
    Green,
    Blue,
    Display,
    Backlight,
    Selector,
    Temperature,
    SensorIn,
    SensorOut,
    Units,
    About
};

/**
 * @brief Represents singular node of the menu tree. Node either has children
 * and works as submenu, or is a leaf representing toggle or detail screen.
 *
 */
struct MenuItem
{
public:
    /**
     * @brief Construct a new MenuItem object representing submenu.
     *
     * @param text Label displayed on the LCD.
     * @param id Node identifier.
     * @param childCount Number of elements in `childs` array.
     * @param childs Pointer to the array of child nodes.
     */
    constexpr MenuItem(const char *text, MenuItemID id, int childCount,
                        const MenuItem *childs)
        : id {id}, text {text}, childs {childs}, childCount {childCount} {}

    /**
     * @brief Construct a new MenuItem object representing leaf.
     *
     * @param text Label displayed on the LCD.
     * @param id Node identifier.
     */
    constexpr MenuItem(const char *text, MenuItemID id)
        : id{id}, text{text}, childs{nullptr}, childCount{0} {}

    MenuItemID id;
    const char* text;
    const MenuItem* childs;
    int childCount;
};

constexpr MenuItem LED_MENU[]
{
    {"Power", MenuItemID::Power},
    {"Red", MenuItemID::Red},
    {"Green", MenuItemID::Green},
    {"Blue", MenuItemID::Blue},
};
constexpr MenuItem DISPLAY_MENU[]
{
    {"Backlight", MenuItemID::Backlight},
    {"Selector", MenuItemID::Selector},
};
constexpr MenuItem TEMP_MENU[]
{
    {"Sensor IN", MenuItemID::SensorIn},
    {"Sensor OUT", MenuItemID::SensorOut},
    {"Units", MenuItemID::Units},
};
constexpr MenuItem MENU_CHILDS[]
{
    {"LED options", MenuItemID::LedOptions, 4, LED_MENU},
    {"Display", MenuItemID::Display, 2, DISPLAY_MENU},
    {"Temperature", MenuItemID::Temperature, 3, TEMP_MENU},
    {"About", MenuItemID::About},
};
constexpr MenuItem MENU
{
    "Menu",
    MenuItemID::Menu,
    4,
    MENU_CHILDS
};
} // namespace menu
