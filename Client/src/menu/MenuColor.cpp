#include "MenuColor.h"

const MenuColor colorWhite = MenuColor("White", "> White", Color::White);
const MenuColor colorBlack = MenuColor("Black", "> Black", Color::Black);
const MenuColor colorPink = MenuColor("Pink", "> Pink", Color::DeepPink);
const MenuColor colorRed = MenuColor("Red", "> Red", Color::Red);
const MenuColor colorMagenta = MenuColor("Magenta", "> Magenta", Color::Magenta);
const MenuColor colorPurple = MenuColor("Purple", "> Purple", Color::Purple);
const MenuColor colorLightOrange = MenuColor("Light Orange", "> Light Orange", Color::Orange);
const MenuColor colorOrange = MenuColor("Orange", "> Orange", Color::OrangeRed);
const MenuColor colorDarkOrange = MenuColor("Dark Orange", "> Dark Orange", Color::Maroon);
const MenuColor colorLightYellow = MenuColor("Light Yellow", "> Light Yellow", Color::Yellow);
const MenuColor colorYellow = MenuColor("Yellow", "> Yellow", Color::Orange);
const MenuColor colorYellowGreen = MenuColor("Yellow Green", "> Yellow Green", Color::GreenYellow);
const MenuColor colorLightGreen = MenuColor("Light Green", "> Light Green", Color::Chartreuse);
const MenuColor colorGreen = MenuColor("Green", "> Green", Color::Green);
const MenuColor colorDarkGreen = MenuColor("Dark Green", "> Dark Green", Color::DarkGreen);
const MenuColor colorLightBlue = MenuColor("Light Blue", "> Light Blue", Color::LightBlue);
const MenuColor colorBlue = MenuColor("Blue", "> Blue", Color::Blue);
const MenuColor colorNavyBlue = MenuColor("Navy Blue", "> Navy Blue", Color::Navy);
const MenuColor colorCyan = MenuColor("Cyan", "> Cyan", Color::Cyan);
const MenuColor colorDarkCyan = MenuColor("Dark Cyan", "> Dark Cyan", Color::DarkCyan);

const MenuColor *menuColors[] = {
    &colorWhite,
    &colorBlack,
    &colorPink,
    &colorRed,
    &colorMagenta,
    &colorPurple,
    &colorLightOrange,
    &colorOrange,
    &colorDarkOrange,
    &colorLightYellow,
    &colorYellow,
    &colorYellowGreen,
    &colorLightGreen,
    &colorGreen,
    &colorDarkGreen,
    &colorLightBlue,
    &colorBlue,
    &colorNavyBlue,
    &colorCyan,
    &colorDarkCyan,
};
const uint8_t numMenuColors = sizeof(menuColors) / sizeof(MenuColor *);

MenuColor::MenuColor(const char *name, const char *label, Color value)
{
    this->name = name;
    this->label = label;
    this->value = value;
}
