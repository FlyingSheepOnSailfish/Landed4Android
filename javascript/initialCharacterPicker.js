//This is a javascript object!
var CharHits = function(character, hits, startIndex, endIndex) {
    this.character = character;
    this.hits = hits;
    this.startIndex = startIndex;
    this.endIndex = endIndex;
}

CharHits.prototype.clone = function() {
    return new CharHits(this.character, this.hits, this.startIndex, this.endIndex);
}

//var CharHits = function(character, hits, startIndex, endIndex) {
//    this.character = character;
//    this.hits = hits;
//    this.startIndex = startIndex;
//    this.endIndex = endIndex;
//}

