import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 1080
    height: 600
    visible: true
    color: "black"
    title: qsTr("Hello World")

    // Variable to hold the input value
    property string inputValue: "0000"
    property bool send: false
    property int i: 0
    property string irValue: "0000"
    property string pcValue: "0X00"
    property int halting: 0

    // Function to refresh the hex grid display
    function updateHexGrid() {
        for (var row = 0; row < 16; row++) {
            for (var col = 0; col < 16; col++) {
                var memoryIndex = row * 16 + col
                // Calculate memory index
                var gridIndex = (row + 1) * 17 + (col + 1)

                // Adjust index for hexGrid
                if (memoryIndex < 256) {
                    hexGrid.children[gridIndex].children[0].text = machine.getMemoryCell(
                                memoryIndex).toUpperCase()
                }
            }
        }
    }

    function updateHexGrid2() {
        for (var row = 0; row < 16; row++) {
            var gridIndex = row * 2
            // Each row has two columns in hexGrid2

            // First column (header row 0 to F)
            hexGrid2.children[gridIndex].children[0].text = row.toString(
                        16).toUpperCase()

            // Second column (register values)
            var registerValue = machine.getRegisterCell(row)
            hexGrid2.children[gridIndex + 1].children[0].text
                    = (registerValue !== null) ? registerValue.toUpperCase(
                                                     ) : "00"
        }
    }

    // Center the window on the screen
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2

    Rectangle {
        x: 307
        y: 174
        width: 745
        height: 407
        anchors.margins: 50
        color: "black"

        // Title
        Text {
            id: name
            x: 309
            y: -34
            width: 128
            height: 39
            text: qsTr("     Memory")
            font.pixelSize: 20
            color: "#FFFFFF"
        }

        Text {
            id: name1
            x: -226
            y: -34
            width: 128
            height: 39
            color: "#ffffff"
            text: qsTr("      Register")
            font.pixelSize: 20
        }

        Text {
            id: name2
            x: 56
            y: -175
            width: 128
            height: 47
            color: "#ffffff"
            text: qsTr("Data input")
            font.pixelSize: 20
        }

        border.color: "#567F94"
        anchors.leftMargin: 173
        anchors.rightMargin: 15
        anchors.topMargin: 150
        anchors.bottomMargin: 19

        // Hexadecimal grid with labels from 0 to F and memory values
        Grid {
            id: hexGrid
            rows: 17
            columns: 17
            spacing: 3.95
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10

            Repeater {
                model: 17 * 17 // Total grid cells

                delegate: Rectangle {
                    width: 40
                    height: 20
                    color: (index % 17 == 0
                            || index < 17) ? "#222" : "#000" // Header cells
                    border.color: "#567F94"

                    Text {
                        anchors.centerIn: parent
                        color: "#FFFFFF"
                        font.pixelSize: 14
                        text: {
                            var gridIndex = index - Math.floor(index / 17)

                            if (index < 17) {
                                // Top header row (0 to F)
                                if (index == 0)
                                    return ""
                                else {

                                    return (index - 1).toString(
                                                16).toUpperCase()
                                }
                            } else if (index % 17 === 0) {
                                // Left header column
                                return Math.floor(gridIndex / 17).toString(
                                            16).toUpperCase(
                                            ) // Adjust for 16 values per row
                            } else {
                                // Memory value cells, starting from index[1][0]
                                var memoryIndex = gridIndex - 17
                                // Adjusted for starting from [1][0]
                                if (memoryIndex >= 0 && memoryIndex < 256) {
                                    // Validating against 0-255
                                    return machine.getMemoryCell(
                                                memoryIndex).toUpperCase(
                                                ) // Ensure the memory value is in uppercase
                                } else {
                                    return "00" // Default value if out of range
                                }
                            }
                        }
                    }
                }
            }
        }

        Button {
            y: -145
            width: 115
            height: 44
            text: "Run"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 508
            anchors.horizontalCenterOffset: 317
            background: Rectangle {
                color: "#567F94"
                border.color: "transparent"
                radius: 4
            }
            onClicked: {
                halting = machine.run()
                updateHexGrid2() // Refresh the hex grid2

                Qt.callLater(function () {
                    irValue = machine.displayIR()
                    pcValue = machine.displayPC()
                    irText.text = "IR: " + irValue // Update the IR display
                    pcText.text = "PC: " + pcValue
                    updateHexGrid() // Call to refresh the hex grid
                })
            }
        }

        Button {
            id: reset
            y: -95
            width: 115
            height: 44
            text: "Reset CPU"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 458
            anchors.horizontalCenterOffset: 199
            background: Rectangle {
                color: "#567F94"
                border.color: "transparent"
                radius: 4
            }
            onClicked: {
                machine.clearRegister()
                updateHexGrid2() // Call to refresh the hex grid
                Qt.callLater(function () {
                    irValue = machine.displayIR()
                    pcValue = machine.displayPC()
                    irText.text = "IR: " + irValue // Update the IR display
                    pcText.text = "PC: " + pcValue
                })
            }
        }

        Button {
            y: -95
            width: 115
            height: 44
            text: "Reset RAM"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 458
            background: Rectangle {
                color: "#567F94"
                radius: 4
                border.color: "#00000000"
            }
            anchors.horizontalCenterOffset: 317
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                machine.clearMemory()
                updateHexGrid() // Call to refresh the hex grid
                irValue = "0000"
                pcValue = "0X00"
                irText.text = "IR: " + irValue // Update the IR display
                pcText.text = "PC: " + pcValue
                row = 0
            }
        }

        Button {
            id: enterButton
            y: -145
            width: 115
            height: 44
            text: "Enter"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 508
            background: Rectangle {
                color: "#567F94"
                radius: 4
                border.color: "#00000000"
            }
            anchors.horizontalCenterOffset: 199
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                // Call the action when the button is clicked
                console.log("Button clicked!")
                // Example actions
                i = machine.setInstructions(inputValue)
                send = true
                updateHexGrid() // Call to refresh the hex grid
                halting = 0
            }
        }

        // Button to show help window
        Button {
            y: -45
            width: 61
            height: 39
            text: "?  Help"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 413
            anchors.horizontalCenterOffset: 344
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                color: "#567F94"
                radius: 4
                border.color: "#00000000"
            }
            onClicked: helpPopup.open()
        }

        // Help Popup
        Popup {
            id: helpPopup
            y: -120
            x: 200
            width: 540
            height: 500
            modal: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            background: Rectangle {
                color: "#000000"
                border.color: "#567f94"
                radius: 4
            }

            Column {
                width: parent.width
                height: parent.height
                spacing: 8
                padding: 5

                // Title
                Text {
                    text: "<b>Operations Set</b>"
                    font.pointSize: 20
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.italic: true
                    color: "white"
                }

                // Scrollable area for the operations set
                ScrollView {
                    width: parent.width
                    height: 400 // Adjust height as needed
                    clip: true

                    // Customize the vertical scroll bar
                    ScrollBar.vertical: ScrollBar {
                        background: Rectangle {
                            color: "#444444"
                            radius: 2
                        }
                        contentItem: Rectangle {
                            width: 12
                            radius: 6
                            color: "#567f94"
                            opacity: 0.8
                        }
                    }

                    Column {
                        spacing: 6

                        // Header Row
                        Row {
                            spacing: 20
                            Text {
                                text: "Opc."
                                font.bold: true
                                font.pointSize: 14
                                color: "white"
                                font.italic: true
                            }
                            Text {
                                text: "Opr."
                                font.bold: true
                                font.pointSize: 14
                                color: "white"
                                font.italic: true
                            }
                            Text {
                                text: "Effect"
                                font.bold: true
                                font.pointSize: 14
                                color: "white"
                                font.italic: true
                            }
                        }

                        // Operations list with aligned rows
                        Repeater {
                            model: [{
                                    "opc": "      1",
                                    "opr": "RXY",
                                    "effect": "Copy the content of RAM cell XY to register R."
                                }, {
                                    "opc": "      2",
                                    "opr": "RXY",
                                    "effect": "Copy the bit-string XY to register R."
                                }, {
                                    "opc": "      3",
                                    "opr": "RXY",
                                    "effect": "Copy the content of register R to RAM cell XY."
                                }, {
                                    "opc": "      4",
                                    "opr": "xRS",
                                    "effect": "Copy the content of register R to register S."
                                }, {
                                    "opc": "      5",
                                    "opr": "RST",
                                    "effect": "Add the content of register S and register T, and put the result in register R. Data is interpreted as integers in two's-complement notation."
                                }, {
                                    "opc": "      6",
                                    "opr": "RST",
                                    "effect": "Add the content of register S and register T, and put the result in register R. Data is interpreted as floats in floating point notation."
                                }, {
                                    "opc": "      7",
                                    "opr": "RST",
                                    "effect": "Bitwise OR (∨) the content of register S and T, and put the result in register R."
                                }, {
                                    "opc": "      8",
                                    "opr": "RST",
                                    "effect": "Bitwise AND (∧) the content of register S and T, and put the result in register R."
                                }, {
                                    "opc": "      9",
                                    "opr": "RST",
                                    "effect": "Bitwise XOR (⊕) the content of register S and T, and put the result in register R."
                                }, {
                                    "opc": "      A",
                                    "opr": "RxX",
                                    "effect": "Rotate the content of register R cyclically right X steps."
                                }, {
                                    "opc": "      B",
                                    "opr": "RXY",
                                    "effect": "Jump to instruction in RAM cell XY if the content of register R equals the content of register 0."
                                }, {
                                    "opc": "      C",
                                    "opr": "xxx",
                                    "effect": " Halt execution."
                                }, {
                                    "opc": "      D",
                                    "opr": "RXY",
                                    "effect": "Jump to instruction in RAM cell XY if the content of register R is greater than (>) the content of register 0. Data is interpreted as integers in two's-complement notation."
                                }, {
                                    "opc": "",
                                    "opr": "",
                                    "effect": ""
                                }]
                            delegate: Row {
                                spacing: 20
                                Text {
                                    text: modelData.opc
                                    font.pointSize: 14
                                    color: "white"
                                    font.italic: true
                                }
                                Text {
                                    text: modelData.opr
                                    font.pointSize: 14
                                    color: "white"
                                    font.italic: true
                                }
                                Text {
                                    text: modelData.effect
                                    font.pointSize: 14
                                    wrapMode: Text.WordWrap
                                    width: 390
                                    color: "white"
                                    font.italic: true
                                }
                            }
                        }

                        // Add a horizontal line
                        Rectangle {
                            id: made
                            width: parent.width * 0.8 // Adjust the width as needed
                            height: 2
                            color: "#567F94" // Same color as the order
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        // Names Section
                        Column {
                            spacing: 4
                            Text {
                                text: ""
                                font.pointSize: 12
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                            }
                            Text {
                                text: "                 Made by"
                                font.pointSize: 18
                                font.italic: true
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter // This is effective only when the width is set appropriately
                                anchors.horizontalCenter: parent.horizontalCenter // Center this Text in the Column
                            }
                            Text {
                                text: "                      Ibrahim Mohamed Saad                20230003"
                                font.pointSize: 12
                                color: "white"
                                font.italic: true
                            }
                            Text {
                                text: "                      Ezzeldin Omar Abdellatif              20230233"
                                font.pointSize: 12
                                color: "white"
                                font.italic: true
                            }
                            Text {
                                text: "                      Ahmed Hussein Mohamed           20230016"
                                font.pointSize: 12
                                color: "white"
                                font.italic: true
                            }
                            Text {
                                text: " "
                                font.pointSize: 12
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }

                // Close button
                Button {
                    text: "Close"
                    width: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    background: Rectangle {
                        color: "#567F94"
                        radius: 4
                        border.color: "#00000000"
                    }
                    onClicked: helpPopup.close()
                }
            }
        }
    }

    Rectangle {
        color: "#000000"
        border.color: "#567F94"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.leftMargin: 14
        anchors.rightMargin: 795
        anchors.topMargin: 174
        anchors.bottomMargin: 19

        // Hexadecimal grid with labels from 0 to F and memory values
        Grid {
            id: hexGrid2
            rows: 16
            columns: 2
            spacing: 5.55
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10

            Repeater {
                model: 16 * 2 // Total grid cells

                delegate: Rectangle {
                    width: 40
                    height: 20
                    color: (index % 2 === 0) ? "#222" : "#000" // Alternate row colors
                    border.color: "#567F94"

                    Text {
                        anchors.centerIn: parent
                        color: "#FFFFFF"
                        font.pixelSize: 14
                        text: {
                            var gridIndex = Math.floor(index / 2)

                            // Calculate the row index
                            if (index % 2 === 0) {
                                // First column (header row 0 to F)
                                return gridIndex.toString(16).toUpperCase(
                                            ) // Hex values from 0 to F
                            } else {
                                // Second column (register values)
                                var registerValue = machine.getRegisterCell(
                                            gridIndex)
                                // If registerValue is null, return "00"
                                return (registerValue !== null) ? registerValue.toUpperCase(
                                                                      ) : "00"
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        color: "#000000"
        border.color: "#567F94"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.leftMargin: 14
        anchors.rightMargin: 274
        anchors.topMargin: 31
        anchors.bottomMargin: 464

        // Input Field
        TextInput {
            id: textInput
            width: 792 // Fixed width
            height: 104 // Height for the input box
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "#FFFFFF"
            font.pixelSize: 30 // Adjusted for better visibility
            maximumLength: 4 // Limit input to 4 characters
            text: inputValue
            verticalAlignment: TextInput.AlignVCenter // Not available; manage with padding
            horizontalAlignment: TextInput.AlignHCenter
            onTextChanged: {
                if (send === true) {
                    textInput.text = "0000" // Resetting input to "0000"
                    send = false // Resetting send for the next input
                } else {
                    inputValue = textInput.text // Update inputValue with current text
                }
            }

            // Capture key events specifically for the TextInput
            Keys.onPressed: {
                if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                    enterButton.clicked() // Trigger the button click action
                    event.accepted = true // Prevent further processing of the event
                }
            }
        }
    }

    Rectangle {
        color: "#222"
        border.color: "#567f94"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.leftMargin: 133
        anchors.rightMargin: 832
        anchors.topMargin: 296
        anchors.bottomMargin: 255

        Text {
            id: irText
            anchors.centerIn: parent
            font.pixelSize: 18
            color: "#FFFFFF"
            text: "IR: " + irValue // Display the IR value
        }
    }

    Rectangle {
        color: "#222"
        border.color: "#567f94"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.leftMargin: 133
        anchors.rightMargin: 832
        anchors.topMargin: 377
        anchors.bottomMargin: 174

        Text {
            id: pcText
            anchors.centerIn: parent
            font.pixelSize: 18
            color: "#FFFFFF"
            text: "PC: " + pcValue // Display the IR value
        }
    }

    Rectangle {
        color: "#000000"
        border.color: "#000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 50
        anchors.leftMargin: 599
        anchors.rightMargin: 310
        anchors.topMargin: 59
        anchors.bottomMargin: 492

        Text {
            id: textMessage
            x: -46
            y: 9
            width: 217
            height: 49
            font.pixelSize: 20
            text: (halting == 1) ? "Opcode not found. Halting" : (i == 1 ? "Out of Range" : (i == 2 ? "Invalid input" : "")) // Conditional text
            color: "red" // Change this to your desired color
            verticalAlignment: Text.AlignCenter // Corrected alignment property
            horizontalAlignment: Text.AlignCenter
            opacity: 0 // Start fully transparent

            // Animation for fading in
            SequentialAnimation on opacity {
                loops: Animation.Infinite // Repeat infinitely
                running: true // Start running immediately

                // Fade in
                NumberAnimation {
                    to: 1 // Fully visible
                    duration: 1000 // 1 second duration
                }

                // Hold
                PauseAnimation {
                    duration: 1000 // Hold for 1 second
                }

                // Fade out
                NumberAnimation {
                    to: 0 // Fully transparent
                    duration: 1000 // 1 second duration
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0}D{i:1;invisible:true}D{i:17}
}
##^##*/

