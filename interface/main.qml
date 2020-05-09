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

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: margin
        rows: 12
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
            Layout.columnSpan: 8
            Layout.rowSpan: 10
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 1/2, 1)
        }

        Rectangle {
            color: "green"
            Layout.columnSpan: 4
            Layout.rowSpan: 6
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 1/2, 1)
        }

        Rectangle {
            color: "green"
            Layout.columnSpan: 8
            Layout.rowSpan: 2
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 1/2, 1)
        }

        Rectangle {
            color: "yellow"
            Layout.columnSpan: 4
            Layout.rowSpan: 6
            Layout.preferredWidth: grid.prefWidth(this, 1/2, 1)
            Layout.preferredHeight: grid.prefHeight(this, 1/2, 1)
            Layout.row: 6
            Layout.column: 8
        }
    }
}
