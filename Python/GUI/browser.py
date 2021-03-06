from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QWidget, QMenu, QPushButton, QSizePolicy
from PyQt5.QtGui import QIcon
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random
import sys


class App(QMainWindow):

    def __init__(self):
        super().__init__()
        self.title = 'Greenpower Monitor'
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        m = PlotCanvas(self, width=5, height=4)
        m.move(0, 0)

        button = QPushButton('PyQt5 button', self)
        button.setToolTip('This s an example button')
        button.move(500, 0)
        button.resize(140, 100)

        self.show()


class PlotCanvas(FigureCanvas):

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)

        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,QSizePolicy.Expanding, QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self.plot()

    def plot(self):
        data = [random.random() for i in range(25)]
        ax = self.figure.add_subplot(111)
        ax.plot_data(data, 'r-')
        ax.plot_data([0, 25], [1, 0], color='b')
        ax.set_title('Battery')
        self.draw()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setStyle('Windows')
    ex = App()
    sys.exit(app.exec_())

# if __name__ == '__main__':
#     app = QApplication([])
#
#     w = QWidget()
#     w.setWindowTitle('Greenpower Monitor')
#     w.show()
#
#     # label = QLabel('Hello World!')
#     # label.show()
#     app.exec_()
