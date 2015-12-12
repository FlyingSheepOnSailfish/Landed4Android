.pragma library
.import "landed.js" as LJS

function geoIntentsURL(lat, lon) {
    var prefix = "geo:";
    var zoom = "?z=15";
    var str = LJS.round(lat,5) + "," + LJS.round(lon,5)+zoom;
    return prefix + str;
}


function dec2bin(dec){
    return (dec >>> 0).toString(2);
}

function hereURL(lat, lon) {
    var prefix = "http://her.is/";
    var latStr = dec2bin(lat);
    var lonStr = dec2bin(lon);
    var base64Str = Qt.btoa(latStr+lonStr);
    //replace chars with special meanins in URLs
    base64Str = base64Str.split('+').join('-'); //replace + with - char
    base64Str = base64Str.split('/').join('_'); // replace / with _ char
    return prefix + base64Str;
}
