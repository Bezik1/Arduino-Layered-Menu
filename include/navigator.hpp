#pragma once

#include "menuItem.hpp"
#include "pins.hpp"

namespace menu
{
/**
 * @brief Tracks position of the user in the two level menu tree. It stores
 * currently opened node and index of the selected child. When submenu is
 * entered, cursor position in the root menu is remembered, so going back
 * restores it.
 *
 */
struct Navigator
{
    /**
     * @brief Returns currently selected menu item.
     *
     * @return const MenuItem& Selected child of the opened node.
     */
    const MenuItem& selectedItem() const
    {
        return parent->childs[selected];
    }

    /**
     * @brief Returns index of the first item on the visible LCD page. List is
     * divided into pages of `pins::LCD_ROWS` items, so cursor always stays on the screen.
     *
     * @return int Index of the item displayed in the first LCD row.
     */
    int firstVisible() const
    {
        return selected - (selected % pins::LCD_ROWS);
    }

    /**
     * @brief Moves cursor by the given number of positions. Cursor wraps
     * around in both directions.
     *
     * @param steps Signed number of positions to move.
     */
    void move(int steps)
    {
        const int count = parent->childCount;
        selected = ((selected + steps) % count + count) % count;
    }

    /**
     * @brief Enters submenu of the selected item.
     *
     * @return bool True if item has children and submenu was opened, false if item is a leaf.
     */
    bool enter()
    {
        const MenuItem& item = selectedItem();
        if (item.childCount == 0)
            return false;

        parent = &item;
        selectedInRoot = selected;
        selected = 0;
        return true;
    }

    /**
     * @brief Returns to the root menu and restores previous cursor position.
     *
     * @return bool True if menu level changed, false if root menu was already opened.
     */
    bool back()
    {
        if (parent == &MENU)
            return false;

        parent = &MENU;
        selected = selectedInRoot;
        return true;
    }

    const MenuItem* parent {&MENU};
    int selected {0};
    int selectedInRoot {0};
};
} // namespace menu
