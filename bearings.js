.pragma library

function formatBearing(bearing) {
    //TODO: some code to format the bearingFrom as human readable compass points (e.g. NNE)

    var bearingRounded = Math.floor(((bearing/45)+1/2))*45;

    var bearingText;

    switch (bearingRounded) {
    case 0:
        //fallthrough
    case 360:
        bearingText = 'N';
        break;
    case 45:
        bearingText = 'NE';
        break;
    case 90:
        bearingText = 'E';
        break;
    case 135:
        bearingText = 'SE';
        break;
    case 180:
        bearingText = 'S';
        break;
    case 225:
        bearingText = 'SW';
        break;
    case 270:
        bearingText = 'W';
        break;
    case 315:
        bearingText = 'NW';
        break;
    }

    /*
            0	N	339	23
            45	NE	24	68
            90	E	69	113
            135	SE	114	158
            180	S	159	203
            225	SW	204	248
            270	W	249	293
            315	NW	294	338
       */
    //return LJS.round(bearing, 0) + "degs";
    return bearingText;
}
