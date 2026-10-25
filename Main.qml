import QtQuick
import QtQuick.Controls

Window {
    id: window
    width: 530
    height: 600
    visible: true
    title: "Chat"

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5

        Row {
            anchors.margins: 5
            spacing: 5

            // Кнопка подключения
            TextField {
                id: ipAdress
                text: "127.0.0.1"
                placeholderText: "Введите IP"
                onAccepted: idBtn.clicked() // если поле селектед и нажимается энтер, идет эмит сигнала кликед для кнопки
            }
            TextField {
                id: ipPort
                text: "11111"
                placeholderText: "Введите порт"
                onAccepted: idBtn.clicked()
            }
            TextField {
                id: nickname
                text: "Dmitrii"
                placeholderText: "Введите имя"
            }
            Button {
                id: idBtn
                text: chatController.isConnected ? "Отключиться" : "Подключиться"
                onClicked: {
                    if (chatController.isConnected)
                        chatController.disconnectFromServer()
                    else
                        chatController.connectToServer(ipAdress.text, parseInt(ipPort.text))
                }
            }
        }

        // Область переписки со скроллом
        ListView {
            id: chatView
            width: parent.width
            height: 400
            clip: true
            model: chatController.messageModel
            spacing: 4
            onCountChanged: chatView.positionViewAtEnd()

            delegate: Text {
                text: "[" + model.sender + "]: " + model.text
                color: model.isMe ? "green" : "black"
            }
        }

        // Ввод
        Row {
            width: parent.width
            spacing: 5

            TextField {
                id: msgInput
                width: parent.width - sendBtn.width - parent.spacing
                placeholderText: "Введите сообщение..."
                onAccepted: sendBtn.clicked()
            }

            Button {
                id: sendBtn
                text: "Отправить"
                onClicked: {
                    if (msgInput.text.length > 0) {
                        chatController.sendMessage(msgInput.text)
                        msgInput.clear()
                    }
                }
            }
        }
    }
}