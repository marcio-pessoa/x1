; x1 Mark I - Useless Machine, G-code program file
;
; Project: x1 Mark I - Useless Machine
; Description: This program is used to test x1 Mark I
;
; Change log:
; 2018-07-18
;        * First version
;
; Header
M111;  Debug mode
M15;  View system info

M81;  Power on

G28;  Finger home

G3 X20  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X15  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X10  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X5  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X3  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X2  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X1  ; Set speed
G29;  Finger out-of-door
G28;  Finger home

G3 X0  ; Set speed
G29;  Finger out-of-door
G28;  Finger home
