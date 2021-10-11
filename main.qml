import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2


Rectangle {
    id: recMain
    color: "#F0F0F0"
    width:8000
    height: 25

    signal quitClicked()

RowLayout{
    spacing: 0
    Button {
        id: buttonOpen
        text: "Open"
        onClicked: fileOpenDialog.visible = true
        Layout.preferredHeight: 25
        Layout.preferredWidth: 70
        background: Rectangle {color: "#F0F0F0"}
    }
    Button {
        id: buttonSave
        text: "Save"
        onClicked: fileSaveDialog.visible = true
        Layout.preferredHeight: 25
        Layout.preferredWidth: 70
        background: Rectangle {color: "#F0F0F0"}
    }

    Button {
        id: buttonQuit
        text: "Quit"
        onClicked: recMain.quitClicked()
        Layout.preferredHeight: 25
        Layout.preferredWidth: 70
        background: Rectangle {color: "#F0F0F0"}
    }
  }

  FileDialog {
      id:fileOpenDialog
      visible: false
      modality: Qt.WindowModal
      title: "Open file"
      folder:"file://"
      nameFilters:["*.txt *.cpp"]
      onAccepted: {
          MyWindow.fileOpen (fileOpenDialog.fileUrls[0])
      }
  }

  FileDialog {
      id:fileSaveDialog
      visible: false
      modality: Qt.WindowModal
      title: "Save file"
      folder:"file://"
      nameFilters:["*.txt *.cpp"]
      selectExisting : false
      onAccepted: {
          MyWindow.fileSave (fileSaveDialog.fileUrls[0])
      }
  }
}





