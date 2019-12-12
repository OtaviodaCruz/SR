clc;
clear;
close;
readChId = 926562;
writeChId = 1;  % replace with your channel number
writeKey = 'JCM7DJHELZHUXJLG'; % Replace with your channel write key
[water,time] = thingSpeakRead(readChId,'Fields',1,'NumPoints',20);
%%water = thingSpeakRead(readChId,'Fields',1,'NumPoints',20);