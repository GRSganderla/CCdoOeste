TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        add.cpp \
        alu.cpp \
        alucontrol.cpp \
        control.cpp \
        formatoi.cpp \
        formatoj.cpp \
        formator.cpp \
        main.cpp \
        memoriadados.cpp \
        memoriainstrucao.cpp \
        mux.cpp \
        novapc.cpp \
        pc.cpp \
        registradores.cpp \
        shiftleft.cpp \
        signextend.cpp \
        simulador.cpp

HEADERS += \
    add.h \
    alu.h \
    alucontrol.h \
    control.h \
    formatoi.h \
    formatoj.h \
    formator.h \
    memoriadados.h \
    memoriainstrucao.h \
    mux.h \
    novapc.h \
    pc.h \
    registradores.h \
    shiftleft.h \
    signextend.h \
    simulador.h
