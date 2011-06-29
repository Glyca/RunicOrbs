#include "BlockInfo.h"
#include <QtGlobal>

BlockInfo::BlockInfo(int value)
{
    data[0] = data[1] = 0;

    setValue(value);
    makePowered(true);
    //qDebug("Dans le contructeur de BlockInfo");
    /*qDebug("Taille d'un INT * 8 = %d", SIZE_OF_A_INT_TIMES_8);
    qDebug("Le numéro de block passé est %d", value);

    qDebug("La valeur de la donnée 1 est %d\nLa valeur de la donnée 2 est %d", data[0], data[1]);*/
    //qDebug("Valeur du bloc : %d", getValue());
    //qDebug("Est alimenté : %d", isPowered());
}

int BlockInfo::getValue() const
{
    // return readShiftMaskBits(data[0], VALUE_BITS_SHIFT, VALUE_BITS_SIZE);
    return i_value;
}

void BlockInfo::setValue(const int value)
{
    //data[0] |= readShiftMaskBits(value, VALUE_BITS_SHIFT, VALUE_BITS_SIZE);
    i_value = value;
}


bool BlockInfo::isPowered() const
{
    //return readShiftMaskBits(data[0], POWERED_BITS_SHIFT, POWERED_BITS_SIZE);
    return b_isPowered;
}

void BlockInfo::makePowered(const bool yes)
{
    //data[0] |= readShiftMaskBits((int)yes, POWERED_BITS_SHIFT, POWERED_BITS_SIZE);
    b_isPowered = yes;
}


