QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adm_atendimentos.cpp \
    adm_cadastro_editar.cpp \
    adm_cadastros.cpp \
    adm_inicio.cpp \
    adm_material.cpp \
    adm_material_editar.cpp \
    main.cpp \
    login.cpp \
    medico_atendimentos.cpp \
    medico_cadastro.cpp \
    medico_inicio.cpp \
    paciente_atendimentos.cpp \
    paciente_cadastro.cpp \
    paciente_inicio.cpp

HEADERS += \
    adm_atendimentos.h \
    adm_cadastro_editar.h \
    adm_cadastros.h \
    adm_inicio.h \
    adm_material.h \
    adm_material_editar.h \
    login.h \
    medico_atendimentos.h \
    medico_cadastro.h \
    medico_inicio.h \
    paciente_atendimentos.h \
    paciente_cadastro.h \
    paciente_inicio.h

FORMS += \
    adm_atendimentos.ui \
    adm_cadastro_editar.ui \
    adm_cadastros.ui \
    adm_inicio.ui \
    adm_material.ui \
    adm_material_editar.ui \
    login.ui \
    medico_atendimentos.ui \
    medico_cadastro.ui \
    medico_inicio.ui \
    paciente_atendimentos.ui \
    paciente_cadastro.ui \
    paciente_inicio.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
