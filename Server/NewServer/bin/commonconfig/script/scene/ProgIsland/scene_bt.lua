

--Level ProgIsland
--Level test_move
evtTouchVolume = 
{ batSequencer, 
    { batPrint, param={ 10 },
    },
    { batWait, param={ 80 },
    },
    { batPrint, param={ 11 },
    },
    { batSpawnSingleNpc, 
    },
    { batPrint, param={ 13 },
    },
};

evtSingleNpcDie = 
{ batSequencer, 
    { batPrint, param={ 23 },
    },
    { batSpawnMediumGroup, 
    },
    { batPrint, param={ 21 },
    },
};

evtMediumGroupDie = 
{ batSequencer, 
    { batPrint, param={ 31 },
    },
    { batSpawnMediumGroup, 
    },
    { batPrint, param={ 33 },
    },
};

evtLargeGroupDie = 
{ batSequencer, 
    { batPrint, param={ 41 },
    },
    { batPrint, param={ 42 },
    },
    { batPrint, param={ 43 },
    },
};
