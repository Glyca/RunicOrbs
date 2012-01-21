#include "WorldBlocks.h"

#include <stdlib.h> // NULL

WorldBlocks::WorldBlocks(const int WORLD_SIZE_X, const int WORLD_SIZE_Y, const int WORLD_SIZE_Z, const int SEA_LEVEL) : i_SIZE_X(WORLD_SIZE_X), i_SIZE_Y(WORLD_SIZE_Y), i_SIZE_Z(WORLD_SIZE_Z), i_SEA_LEVEL(SEA_LEVEL)
{
    int size = i_SIZE_X * i_SIZE_Y * i_SIZE_Z;
    p_BlocksInfo = new BlockInfo[size];
}

void WorldBlocks::generate(int seed)
{
	qDebug("Génération du monde...");
	qDebug("Taille demandée : (x=%d; y=%d; z=%d) sea_level : %d", i_SIZE_X, i_SIZE_Y, i_SIZE_Z, i_SEA_LEVEL);

    // de la surface jusq'au dessus
    for(int j = (i_SIZE_Y - i_SEA_LEVEL); j < (i_SIZE_Y); j++)
    {
	for(int i = 0; i < i_SIZE_X; i++)
	{
	    for(int k = 0; k < i_SIZE_Z; k++)
	    {
		// On ne met que du vide
		block(i, j, k)->setValue(0);
	    }
	}
    }

    // de la surface jusq'en dessous
    for(int j = (i_SIZE_Y - i_SEA_LEVEL); j >= 0; j--)
    {
	for(int i = 0; i < i_SIZE_X; i++)
	{
	    for(int k = 0; k < i_SIZE_Z; k++)
	    {
		// Il y a une grosse proba d'avoir de la roche, puis un peu de terre, puis rarerent un trou
		int random = rand() % 9;
		// 0, 1, 2, 3, 4, 5 -> Roche
		if(random <= 5) block(i, j, k)->setValue(1);
		// 6, 7 -> Terre
		if(random == 6 || random == 7) block(i, j, k)->setValue(2);
		// 8 -> Vide
		if(random == 8) block(i, j, k)->setValue(0);
	    }
	}
    }
	qDebug("Génération du monde terminée !");
	qDebug("Poids brut total : %d Kio", (i_SIZE_X * i_SIZE_Y * i_SIZE_Z * sizeof(BlockInfo)) >> 10);
}
