#include "MenuColor.h"



const MenuColor colorWhite = MenuColor("White", Color::White);
const MenuColor colorBlack = MenuColor("Black", Color::Black);
const MenuColor colorRed = MenuColor("Red", Color::Red);
const MenuColor colorGreen = MenuColor("Green", Color::Green);
const MenuColor colorBlue = MenuColor("Blue", Color::Blue);
const MenuColor colorMaroon = MenuColor("Maroon", Color::Maroon);
const MenuColor colorSalmon = MenuColor("Salmon", Color::Salmon);
const MenuColor colorPink = MenuColor("Pink", Color::Pink);
const MenuColor colorDeepPink = MenuColor("Deep Pink", Color::DeepPink);
const MenuColor colorMagenta = MenuColor("Magenta", Color::Magenta);
const MenuColor colorPurple = MenuColor("Purple", Color::Purple);
const MenuColor colorLightBlue = MenuColor("Light Blue", Color::LightBlue);
const MenuColor colorNavyBlue = MenuColor("Navy Blue", Color::Navy);
const MenuColor colorLightGreen = MenuColor("Light Green", Color::LightGreen);
const MenuColor colorChartreuse = MenuColor("Chartreuse", Color::Chartreuse);
const MenuColor colorCyan = MenuColor("Cyan", Color::Cyan);
const MenuColor colorDarkCyan = MenuColor("Dark Cyan", Color::DarkCyan);
const MenuColor colorOrange = MenuColor("Orange", Color::Orange);
const MenuColor colorOrangeRed = MenuColor("Orange Red", Color::OrangeRed);
const MenuColor colorDarkOrange = MenuColor("Dark Orange", Color::DarkOrange);
const MenuColor colorYellow = MenuColor("Yellow", Color::Yellow);
const MenuColor colorYellowGreen = MenuColor("Yellow Green", Color::YellowGreen);

const MenuColor *menuColors[] = {&colorWhite, &colorBlack, &colorRed, &colorGreen,
                                 &colorBlue, &colorMaroon, &colorSalmon, &colorPink,
                                 &colorDeepPink, &colorMagenta,
                                 &colorPurple, &colorLightBlue, &colorNavyBlue,
                                 &colorLightGreen, &colorChartreuse,
                                 &colorCyan, &colorDarkCyan, &colorOrange,
                                 &colorOrangeRed, &colorDarkOrange, &colorYellow,
                                 &colorYellowGreen};
const uint8_t numMenuColors = sizeof(menuColors)/sizeof(MenuColor*);


MenuColor::MenuColor(const char *name, Color value)
{
    this->name = name;
    this->value = value;
}

