function varargout = pds2(varargin)

% Last Modified by GUIDE v2.5 01-Jul-2021 15:28:45

%Inicio da inicialização do código
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @pds2_OpeningFcn, ...
                   'gui_OutputFcn',  @pds2_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
%Fim da inicialização do código 


function pds2_OpeningFcn(hObject, ~, handles, varargin)

handles.output = hObject;
guidata(hObject, handles);


function varargout = pds2_OutputFcn(~, ~, handles)
varargout{1} = handles.output;



function b1_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=264;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b2_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=297;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b3_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=330;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b4_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=352;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b5_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=396;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b6_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=440;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)



function b7_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=495;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)


function b8_Callback(~, ~, ~)

t=0.5;
fs=8000;
f1=528;
NS=fs*t;
n=[0:NS-1];
omega=(2*pi*f1)/fs;
y=0.5*cos(omega*n);
sound(y,fs)



function close_Callback(~, ~, ~)
close;

