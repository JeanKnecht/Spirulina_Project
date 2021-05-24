import PySimpleGUI as sg
import serial
import datetime


ser = serial.Serial("COM3", "9600")

def tijd_regime(event, window, number):
    if event == "Licht uit":
        ser.write(bytes((f"{number}1"), 'utf-8'))
        window.close()

    if event == "Licht aan":
        ser.write(bytes((f"{number}2"), 'utf-8'))
        window.close()
        

    if event == "Flikker(500ms)":
        ser.write(bytes((f"{number}3"), 'utf-8'))
        window.close()
        


def strobo_window(strobo_num, real_num):
    layout = [[sg.Text(f"Stroboscoop_{strobo_num}",font=("Helvetica", 15))],
            [sg.Button("Licht aan",bind_return_key=True,)],
            [sg.Button("Licht uit", bind_return_key=True)],
            [sg.Button("Flikker(500ms)", bind_return_key=True)]]
    
    window2 = sg.Window("Second Window", layout, size=(200,200))
    while True:
        event, values = window2.read()
        if event == "Exit" or event == sg.WIN_CLOSED:
            break
        global s
        s = f"{event} om {datetime.datetime.now()}"
        tijd_regime(event, window2,real_num)

        
    window2.close()

layout = [
    [sg.Txt("Gegevens Stroboscoop",font=("Helvetica", 15))],
    [sg.Txt("---"*100)],
    [sg.Button("Strobo_1",bind_return_key=True,)],
    [sg.Txt(size=(30,1), key='S1')],
    [sg.Button("Strobo_2", bind_return_key=True)],
    [sg.Txt(size=(30,1), key='S2')],
    [sg.Button("Strobo_3", bind_return_key=True)],
    [sg.Txt(size=(30,1), key='S3')],
    [sg.Button("Strobo_4", bind_return_key=True)],
    [sg.Txt(size=(30,1), key='S4')],
    [sg.Button("Strobo_5", bind_return_key=True)],
    [sg.Txt(size=(30,1), key='S5')],
    [sg.Button("Strobo_6", bind_return_key=True)],
    [sg.Txt(size=(30,1), key='S6')],
]
def tijd():
     window.Element('tijd').Update(str(datetime.datetime.now()))
window = sg.Window('Spirulina', layout, size=(500,500))
while True:
    event, values = window.Read()
    print(event, values)
    try:
        if event == sg.WIN_CLOSED or event == 'Exit':
            break

        if event == "Strobo_1":
            strobo_window(1,2)
            window.Element('S1').Update(s)

        if event == "Strobo_2":
            strobo_window(2,3)
            window.Element('S2').Update(s)

        if event == "Strobo_3":
            strobo_window(3,4)
            window.Element('S3').Update(s)

        if event == "Strobo_4":
            strobo_window(4,5)
            window.Element('S4').Update(s)

        if event == "Strobo_5":
            strobo_window(5,6)
            window.Element('S5').Update(s)

        if event == "Strobo_6":
            strobo_window(6,7)
            window.Element('S6').Update(s)

    except KeyboardInterrupt:
        break

window.close()