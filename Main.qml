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
        //anchors.leftMargin: 0
        //anchors.rightMargin: 20
        // anchors.topMargin: 0
        // anchors.bottomMargin: 20
        spacing: 5
        Row {
            //anchors.fill: parent
            anchors.margins: 5
            spacing: 5

            //Кнопка подключения
            TextField {
                id: ipAdress
                text: "127.0.0.1"
                //width: parent.width - 90
                placeholderText: "Введите IP"
                onAccepted: idBtn.clicked()//если поле селектед и нажимается энтер, идет эмит сигнала кликед для кнопки
            }
            TextField {
                id: ipPort
                text: "11111"
                //width: parent.width - 90
                placeholderText: "Введите порт"
                onAccepted: idBtn.clicked()
            }
            TextField {
                id: nickname
                text: "Dmitrii"
                //width: parent.width - 90
                placeholderText: "Введите имя"
                //onAccepted: idBtn.clicked()
            }
            Button {
                id: idBtn
                text: "Подключиться"
                onClicked: host.connectToServer(ipAdress.text, parseInt(ipPort.text))
            }
        }

        //Область переписки со скроллом
        ListView {
            id: chatView
            width: parent.width
            height: 400
            clip: true
            model: chatModel
            spacing: 4
            onCountChanged: chatView.positionViewAtEnd()

            delegate: Text {
                text: "[" + model.sender + "]: " + model.text
                color: model.isMe ? "green" : "black"
            }
        }

        //ввод
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
                //width: 80
                text: "Отравить"
                onClicked: {
                    if (msgInput.text.length > 0) {
                        host.sendMessage(msgInput.text)
                        msgInput.clear()
                    }
                }
            }
        }
    }
}