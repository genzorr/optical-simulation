import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: root
    visible: true
    title: "Optical simulation"
    property int margin: 10
    width: 800
    height: 600
//    width: grid.implicitWidth + 2 * margin
//    height: grid.implicitHeight + 2 * margin
//    minimumWidth: grid.Layout.minimumWidth + 2 * margin
//    minimumHeight: grid.Layout.minimumHeight + 2 * margin

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: margin
        rows: 13
        columns: 12
        columnSpacing: margin
        rowSpacing: margin

        property double colWidth: parent.width/columns
        property double rowHeight: parent.height/rows

        function prefWidth(item, spaceCoeff, marginCoeff){
            return ((colWidth * item.Layout.columnSpan)) - columnSpacing * spaceCoeff - margin * marginCoeff
        }
        function prefHeight(item, spaceCoeff, marginCoeff){
            return ((rowHeight * item.Layout.rowSpan)) - rowSpacing * spaceCoeff - margin * marginCoeff
        }

        Rectangle {
            color: "red"
            Layout.columnSpan: 12
            Layout.rowSpan: 1
            Layout.preferredWidth: grid.prefWidth(this, 0, 2)
            Layout.preferredHeight: grid.prefHeight(this, 2/3, 2/3)
        }

        Rectangle {
            color: "green"
            Layout.columnSpan: 6
            Layout.rowSpan: 10
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 2/3, 2/3)
        }

        Rectangle {
            color: "green"
            Layout.columnSpan: 6
            Layout.rowSpan: 10
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 2/3, 2/3)
        }

        Rectangle {
            color: "yellow"
            Layout.columnSpan: 12
            Layout.rowSpan: 2
            Layout.preferredWidth: grid.prefWidth(this, 0, 2)
            Layout.preferredHeight: grid.prefHeight(this, 2/3, 2/3)
        }
    }
}
/*
    RowLayout {
        id: row
        anchors.fill: parent
        anchors.margins: root.margin
        spacing: 10

        ColumnLayout {
            id: col1
            spacing: 10
//            Layout.preferredWidth: 0.7*parent.width
            Layout.fillWidth: true
            column: 6

           Rectangle {
                id: fieldRect
                color: 'red'
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Rectangle {
                id: logRect
                color: 'green'
                Layout.preferredHeight: 0.2*parent.height
                Layout.fillWidth: true
            }
        }

        ColumnLayout {
            id: col2
            spacing: 10
            Layout.preferredWidth: 0.3*parent.width
            Layout.fillWidth: false

           Rectangle {
                id: imageRect
                color: 'blue'
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Rectangle {
                id: objectRect
                color: 'yellow'
                Layout.preferredHeight: 0.5*parent.height
                Layout.fillWidth: true
            }
        }
    }
*//*

}
*/
