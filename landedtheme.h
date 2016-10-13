#ifndef LANDEDTHEME_H
#define LANDEDTHEME_H
#include <QObject>
#include <QColor>
class LandedTheme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int MarginSmall READ MarginSmall CONSTANT)
    Q_PROPERTY(int MarginText READ MarginText CONSTANT)

    Q_PROPERTY(QColor BackgroundColorA READ BackgroundColorA CONSTANT)
    Q_PROPERTY(QColor BackgroundColorB READ BackgroundColorB CONSTANT)
    Q_PROPERTY(QColor BackgroundColorC READ BackgroundColorC CONSTANT)
    Q_PROPERTY(QColor BackgroundColorD READ BackgroundColorD CONSTANT)
    Q_PROPERTY(QColor BackgroundColorE READ BackgroundColorE CONSTANT)

    Q_PROPERTY(QColor TextColorActive READ TextColorActive CONSTANT)
    Q_PROPERTY(QColor TextColorEmergency READ TextColorEmergency CONSTANT)
    Q_PROPERTY(QColor TextColorInactive READ TextColorInactive CONSTANT)
    Q_PROPERTY(QColor LabelColorActive READ LabelColorActive CONSTANT)
    Q_PROPERTY(QColor LabelColorInactive READ LabelColorInactive CONSTANT)

    Q_PROPERTY(QColor ButtonColorGreen READ ButtonColorGreen CONSTANT)
    Q_PROPERTY(QColor ButtonColorRed READ ButtonColorRed CONSTANT)
    Q_PROPERTY(QColor ButtonColorGrey READ ButtonColorGrey CONSTANT)
    Q_PROPERTY(QColor ButtonColorWhite READ ButtonColorWhite CONSTANT)

    Q_PROPERTY(int LabelWidthShort READ LabelWidthShort CONSTANT)
    Q_PROPERTY(int LabelWidthLong READ LabelWidthLong CONSTANT)

    Q_PROPERTY(int ListItemHeight READ ListItemHeight CONSTANT)

    Q_PROPERTY(int FontSizeVeryLarge READ FontSizeVeryLarge CONSTANT)
    Q_PROPERTY(int FontSizeLarge READ FontSizeLarge CONSTANT)
    Q_PROPERTY(int FontSizeMedium READ FontSizeMedium CONSTANT)
    Q_PROPERTY(int FontSizeSmall READ FontSizeSmall CONSTANT)
    Q_PROPERTY(int FontSizeVerySmall READ FontSizeVerySmall CONSTANT)

    Q_PROPERTY(int TopMarginLarge READ TopMarginLarge CONSTANT)
    Q_PROPERTY(int TopMarginMedium READ TopMarginMedium CONSTANT)
    Q_PROPERTY(int TopMarginSmall READ TopMarginSmall CONSTANT)

public:
    LandedTheme(QObject* parent = 0) : QObject(parent) {}

    int MarginSmall() const { return 10;}
    int MarginText() const { return 0;} //as sailfish is transparent, no margin needed on textarea / text edit etc.

    QColor BackgroundColorA() const { return "#101010";}
    QColor BackgroundColorB() const { return "transparent";}
    QColor BackgroundColorC() const { return "transparent";}
    QColor BackgroundColorD() const { return "transparent";}
    QColor BackgroundColorE() const { return "transparent";}

    //QColor textColorActive() const { return  "black";}
    QColor TextColorActive() const { return  "orange";}
    QColor TextColorEmergency() const { return  "red";}
    QColor TextColorInactive() const { return "grey";}
    QColor LabelColorActive() const { return "green";}
    //QColor LabelColorActive() const { return "lightgrey";}
    QColor LabelColorInactive() const { return "grey";}

    QColor ButtonColorGreen() const { return "lightgreen";}
    QColor ButtonColorRed() const { return "red";}
    QColor ButtonColorGrey() const { return "grey";}
    QColor ButtonColorWhite() const { return "white";}

    //int LabelWidthShort() const {return 130;} //sailfish
    //int LabelWidthLong() const {return 320;} //sailfish
    int LabelWidthShort() const {return 360;}
    int LabelWidthLong() const {return 840;}

    //int ListItemHeight() const {return 70;} //sailfish
    int ListItemHeight() const {return 170;}

    int FontSizeVeryLarge() const { return 144;}
    int FontSizeLarge() const { return 120;}
    int FontSizeMedium() const { return 90;}
    int FontSizeSmall() const { return 48;}
    int FontSizeVerySmall() const { return 32;}

    int TopMarginLarge() const { return 100;}
    int TopMarginMedium() const { return 50;}
    int TopMarginSmall() const { return 25;}

    /*
    //harmattan
    int MarginSmall() const { return 10;}
    int MarginText() const { return 10;}
    QColor BackgroundColorA() const { return "black";}
    QColor BackgroundColorB() const { return "white";}
    QColor BackgroundColorC() const { return "lightyellow";}
    QColor BackgroundColorD() const { return "red";}
    QColor BackgroundColorE() const { return "green";}
    */
};
#endif // LANDEDTHEME_H
