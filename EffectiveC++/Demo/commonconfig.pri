
OUT_ROOT_DIR=$$PWD/../out/Demo

CONFIG(debug,debug|release){
    DESTDIR += $$OUT_ROOT_DIR/target/debug
    OBJECTS_DIR += $$OUT_ROOT_DIR/tmp/debug/$$TARGET
    MOC_DIR += $${OBJECTS_DIR}
    RCC_DIR += $${OBJECTS_DIR}
    UI_DIR += $${OBJECTS_DIR}
}else{

    DESTDIR += $$OUT_ROOT_DIR/target/release
    OBJECTS_DIR += $$OUT_ROOT_DIR/tmp/release/$$TARGET
    MOC_DIR += $${OBJECTS_DIR}
    RCC_DIR += $${OBJECTS_DIR}
    UI_DIR += $${OBJECTS_DIR}
}
