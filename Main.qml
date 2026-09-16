import QtQuick
import QtQuick.Controls
import host

Window {
    width: 480
    height: 600
    visible: true
    title: "Qt Quick Chat"
    MyHost {
        id: client

        onToUiConnected: {
            chatLog.append("[Система]: Подключено к серверу!\n")
        }
        onToUiDisconneted: {
            chatLog.append("[Система]: Соединение разорвано.\n")
        }
        onToUiNewMessage: (message) => {
            chatLog.append("[Сервер]: " + message + "\n")
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        anchors.leftMargin: 0
        anchors.rightMargin: 20
        anchors.topMargin: 0
        anchors.bottomMargin: 20
        spacing: 10

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
        Button {
            id: idBtn
            text: "Подключиться"
            onClicked: client.connectToServer(ipAdress.text, parseInt(ipPort.text))
        }

        //Область переписки
        TextArea {
            id: chatLog
            width: parent.width
            height: 400
            readOnly: true
            wrapMode: TextEdit.Wrap
            background: Rectangle { border.color: "#cccccc" }
        }

        //ввод
        Row {
            width: parent.width
            spacing: 8

            TextField {
                id: msgInput
                width: parent.width - 90
                placeholderText: "Введите сообщение..."
                onAccepted: sendBtn.clicked()
            }

            Button {
                id: sendBtn
                width: 80
                text: "send"
                onClicked: {
                    if (msgInput.text.length > 0) {
                        client.sendMessage(msgInput.text)
                        chatLog.append("[Dmitrii]: " + msgInput.text + "\n")
                        msgInput.clear()
                    }
                }
            }
        }
    }
}
