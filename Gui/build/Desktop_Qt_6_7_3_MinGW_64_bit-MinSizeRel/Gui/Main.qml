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

        // Button definitions (unchanged)
        Button {
            y: -138
            width: 115
            height: 44
            text: "Run"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 501
            anchors.horizontalCenterOffset: 317
            background: Rectangle {
                color: "#567F94"
                border.color: "transparent" // Optional: makes the border invisible
                radius: 4 // Optional: adds rounded corners
            }
            onClicked: {
                machine.run()
            }
        }

        Button {
            y: -88
            width: 115
            height: 44
            text: "Clear Register"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 451
            anchors.horizontalCenterOffset: 199
            background: Rectangle {
                color: "#567F94"
                border.color: "transparent"
                radius: 4
            }
        }

        Button {
            y: -88
            width: 115
            height: 44
            text: "Clear Memory"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 451
            background: Rectangle {
                color: "#567F94"
                radius: 4
                border.color: "#00000000"
            }
            anchors.horizontalCenterOffset: 317
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            y: -138
            width: 115
            height: 44
            text: "Enter"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 501
            background: Rectangle {
                color: "#567F94"
                radius: 4
                border.color: "#00000000"
            }
            anchors.horizontalCenterOffset: 199
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                i = machine.setInstructions(inputValue)
                send = true
                updateHexGrid() // Call to refresh the hex grid
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
                    inputValue = "0000"
                    console.log("hello")
                    send = false
                } else {
                    inputValue = textInput.text
                    console.log("hello1")
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
            x: 0
            y: 10
            width: 171
            height: 49
            font.pixelSize: 20
            text: (i == 1) ? "out of range" : "" // Use a ternary operator for conditional text
            color: "red" // Change this to your desired color
            verticalAlignment: textMessage.AlignVCenter // Not available; manage with padding
            horizontalAlignment: textMessage.AlignHCenter
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
