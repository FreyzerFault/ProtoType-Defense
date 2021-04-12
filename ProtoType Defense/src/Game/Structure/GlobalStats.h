#pragma once

// Al ser STATIC se crea una variable independiente por cada include
// Si se modifica, los cambios solo seran visibles por la clase que lo modifico

// ENEMY

static int baseLife = 100;
static int baseSpeed = 100;
static int baseKillReward = 10;



// WAVE

static int baseNumEnemies = 10;
static int baseDelay = 2; // Secs
static float baseFrecuency = 2; // Enemy per Sec



// ROUND

static int baseRoundReward = 100;
static int baseNumWaves = 1;




// PLAYER

static int initialLives = 100;
static int initialMoney = 600;