import QtQuick
import QtQuick.Controls
import host

Window {
    id: window
    width: 500
    height: 600
    visible: true
    title: "Chat"
    ListModel{
        id:chat
    }
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
        //anchors.leftMargin: 0
        //anchors.rightMargin: 20
        // anchors.topMargin: 0
        // anchors.bottomMargin: 20
        spacing: 5
        Row{
            //anchors.fill: parent
            anchors.margins: 10
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
            Button {
                id: idBtn
                text: "Подключиться"
                onClicked: client.connectToServer(ipAdress.text, parseInt(ipPort.text))
            }
        }
        //Область переписки со скроллом
        ScrollView {
            width: parent.width
            height: 400
            clip: false

            //Область переписки
            TextArea {
                id: chatLog
                readOnly: true
                width: parent.width//скролл длиннее чем окно переписки
               height: parent.height
                wrapMode: TextEdit.Wrap//перенос текста который шире чем ширина строки
                // background: Rectangle { border.color: "#cccccc" }
                onTextChanged: cursorPosition = length

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
                        client.sendMessage(msgInput.text)
                        chatLog.append("[Dmitrii]: " + msgInput.text + "\n")
                        msgInput.clear()
                    }
                }
            }
        }
    }
}
