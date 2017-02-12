import QtQuick 2.0

import QtQuick.Controls 1.2
//import QtQuick.Layouts 1.0
//import QtQuick.Dialogs 1.1
//import QtQuick.Window 2.1



ApplicationWindow {
    Action {
        id: alignLeftAction
        text: "&Left"
        iconSource: "images/textleft.png"
        iconName: "format-justify-left"
        shortcut: "ctrl+l"
        onTriggered: document.alignment = Qt.AlignLeft
        checkable: true
        checked: document.alignment == Qt.AlignLeft
    }
    Action {
        id: alignCenterAction
        text: "C&enter"
        iconSource: "images/textcenter.png"
        iconName: "format-justify-center"
        onTriggered: document.alignment = Qt.AlignHCenter
        checkable: true
        checked: document.alignment == Qt.AlignHCenter
    }
    Action {
        id: alignRightAction
        text: "&Right"
        iconSource: "images/textright.png"
        iconName: "format-justify-right"
        onTriggered: document.alignment = Qt.AlignRight
        checkable: true
        checked: document.alignment == Qt.AlignRight
    }
    Action {
        id: alignJustifyAction
        text: "&Justify"
        iconSource: "images/textjustify.png"
        iconName: "format-justify-fill"
        onTriggered: document.alignment = Qt.AlignJustify
        checkable: true
        checked: document.alignment == Qt.AlignJustify
    }

    Action {
        id: boldAction
        text: "&Bold"
        iconSource: "images/textbold.png"
        iconName: "format-text-bold"
        onTriggered: document.bold = !document.bold
        checkable: true
        checked: document.bold
    }

    Action {
        id: italicAction
        text: "&Italic"
        iconSource: "images/textitalic.png"
        iconName: "format-text-italic"
        onTriggered: document.italic = !document.italic
        checkable: true
        checked: document.italic
    }
    Action {
        id: underlineAction
        text: "&Underline"
        iconSource: "images/textunder.png"
        iconName: "format-text-underline"
        onTriggered: document.underline = !document.underline
        checkable: true
        checked: document.underline
    }
}
