import socket
import os
import json

def printHeader():
        os.system('clear')
        print ('Welcome to Milestone 4 Demo')
        return

def printMotor ( lefts, leftd, rights, rightd  ):
        print ('\n\nLeft RPM:', lefts )
        if (leftd != '0'):
                print ('\nLeft Direction: FORWARD' )
        else:
                print ('\nLeft Direction: REVERSE' )
        print ('\nRight RPM:', rights )
        if (rightd != '0'):
                print ('\nRight Direction: FORWARD' )
        else:
                print ('\nRight Direction: REVERSE')

def printLineSet ( li0, li1, li2, li3, li4, li5, li6, li7 ):
        print ('\n\nCurrent line sensor data:')
        print ('\n 0 1 2 3 4 5 6 7')
        print ('\n | | | | | | | |')
        print ('\n', str(li0), str(li1), str(li2), str(li3), str(li4), str(li5), str(li6), str(li7))

def printSequence (seqnum):
        print('\n\nLast Sequence Number: ', seqnum)

def printMessageType (type):
        print('\n\nThe last non-empty received message type was:', type)

globPrev = 's'

def printData():
        #printHeader()
        #printSequence(seq)
        #printMessageType(lmt)
        #printMotor( spl, dil, spr, dir  )
        printLineSet(l0, l1, l2, l3, l4, l5, l6, l7)


def parseLine(ln1, ln2, ln3, ln4, ln5, ln6, ln7, ln8, globPrev):
        prev = globPrev
        #line on center
        if (ln4 == '1'or ln5 == '1') and ln1 == '0' and ln3 == '0' and ln2 == '0' and ln6 == '0' and ln7 == '0' and ln8 == '0':
                prev = 'c'
                #client.send(prev.encode('ascii'))
                print("center")
                return 'c'
        #line on left
        elif (ln6 == '1' or ln7 == '1' or ln8 == '1') and ln1 == '0' and ln2 == '0' and ln3 == '0':
                if prev == 'r':
                        prev = '0'
                        #client.send(prev.encode('ascii'))
                        return '0'
                else:
                        prev = 'l'
                        print('left')
                        #client.send(prev.encode('ascii'))
                        return 'l'

        #line on right
        elif (ln1 == '1' or ln2 == '1' or ln3 == '1') and ln6 == '0' and ln7 == '0' and ln8 == '0':
                if prev == 'l':
                        prev = '0'
                        #client.send(prev.encode('ascii'))
                        return '0'
                else:
                        prev = 'r'
                        #client.send(prev.encode('ascii'))
                        print("right")
                        return 'r'
        elif ln1 == '0' and ln2 == '0' and ln3 == '0' and ln4 == '0' and ln5 == '0' and ln6 == '0' and ln7 == '0' and ln8 == '0':
                return 'r'
        else:
                prev = '0'
                #client.send(prev.encode('ascii'))
                print("prev")
                return '0'


host = ''
port = 2000
backlog = 5
size = 1024

typ = 'n'
lmt = 'n'
seq = 0
dil = 0
dir = 0
spl = 0
spr = 0
l0 = 0
l1 = 0
l2 = 0
l3 = 0
l4 = 0
l5 = 0
l6 = 0
l7 = 0

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(backlog)
file = open("output.txt", "w")
print ('server started and listening')
gprev = 'c'
while True:
        client, address = s.accept()
        print('accepted')
        while True:
                data = client.recv(size)
                file.write(str(data) + '\n')
                if data:
                        try:
                                data = data.decode('ascii')
                                #print("data: " + data)
                                j = json.loads(data)
                                if (j['typ'] == 'm'):
                                        typ = j['typ']
                                        seq = j['seq']
                                        dil = j['dil']
                                        dir = j['dir']
                                        spl = j['spl']
                                        spr = j['spr']
                                        #printData()

                                if (j['typ'] == 'l'):
                                        typ = j['typ']
                                        seq = j['seq']
                                        l0 = j['li0']
                                        l1 = j['li1']
                                        l2 = j['li2']
                                        l3 = j['li3']
                                        l4 = j['li4']
                                        l5 = j['li5']
                                        l6 = j['li6']
                                        l7 = j['li7']
                                        print("seq: " + seq)
                                        gprev = parseLine(str(l0), str(l1), str(l2), str(l3), str(l4), str(l5), str(l6), str(l7), gprev)
                                        client.send(gprev.encode('ascii'))
                                        print("gprev: " + str(gprev))
                                        printData()


                                if (j['typ'] == 'n'):
                                        typ = j['typ']
                                        seq = j['seq']
                                        #printData()

                                if (typ != 'n'):
                                        lmt = typ
                        except Exception as e:
                                print(str(e))


client.close()