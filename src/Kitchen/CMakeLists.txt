set(PATH_H
        inc/Kitchen/)
set(PATH_S
        src/Kitchen/)

set(SOURCES
        ${PATH_S}KitchenManager.cpp
        ${PATH_S}PlazzaKitchens.cpp
        ${PATH_S}Stock.cpp
        ${PATH_S}Kitchen.cpp
        ${PATH_S}ThreadPool.cpp
        )

set(HEADERS
        ${PATH_H}KitchenManager.hpp
        ${PATH_H}PlazzaKitchens.hpp
        ${PATH_H}Stock.hpp
        ${PATH_H}Kitchen.hpp
        ${PATH_H}ThreadPool.hpp
        ${PATH_H}PizzaCooking.hpp
        ${PATH_H}StockConsume.hpp
        )

set(KITCHEN_FILES
        ${SOURCES}
        ${HEADERS}
        )