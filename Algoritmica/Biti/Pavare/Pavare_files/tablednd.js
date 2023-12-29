var currenttable=null;document.onmousemove=function(ev){if(currenttable&&currenttable.dragObject){ev=ev||window.event;var mousePos=currenttable.mouseCoords(ev);var y=mousePos.y- currenttable.mouseOffset.y;if(y!=currenttable.oldY){var movingDown=y>currenttable.oldY;currenttable.oldY=y;var currentRow=currenttable.findDropTargetRow(y);if(currentRow){if(movingDown&&currenttable.dragObject!=currentRow){currenttable.dragObject.parentNode.insertBefore(currenttable.dragObject,currentRow.nextSibling);recolorTable(currenttable.dragObject.parentNode.parentNode);}else if(!movingDown&&currenttable.dragObject!=currentRow){currenttable.dragObject.parentNode.insertBefore(currenttable.dragObject,currentRow);recolorTable(currenttable.dragObject.parentNode.parentNode);}}}
return false;}}
document.onmouseup=function(ev){if(currenttable&&currenttable.dragObject){var droppedRow=currenttable.dragObject;droppedRow.style.backgroundColor='transparent';currenttable.dragObject=null;currenttable.onDrop(currenttable.table,droppedRow);currenttable=null;}}
function getEventSource(evt){if(window.event){evt=window.event;return evt.srcElement;}else{return evt.target;}}
function initialize(){forEach(document.getElementsByTagName('table'),function(table){if(table.className.search(/\bdragndrop\b/)!=-1){var tableDnD=new TableDnD();tableDnD.init(table);}});}
function TableDnD(){this.dragObject=null;this.mouseOffset=null;this.table=null;this.oldY=0;this.init=function(table){this.table=table;var rows=table.tBodies[0].rows;for(var i=0;i<rows.length;i++){var nodrag=rows[i].getAttribute("NoDrag")
if(nodrag==null||nodrag=="undefined"){this.makeDraggable(rows[i]);}}}
this.onDrop=function(table,droppedRow){}
this.getPosition=function(e){var left=0;var top=0;if(e.offsetHeight==0){e=e.firstChild;}
while(e.offsetParent){left+=e.offsetLeft;top+=e.offsetTop;e=e.offsetParent;}
left+=e.offsetLeft;top+=e.offsetTop;return{x:left,y:top};}
this.mouseCoords=function(ev){if(ev.pageX||ev.pageY){return{x:ev.pageX,y:ev.pageY};}
return{x:ev.clientX+ document.body.scrollLeft- document.body.clientLeft,y:ev.clientY+ document.body.scrollTop- document.body.clientTop};}
this.getMouseOffset=function(target,ev){ev=ev||window.event;var docPos=this.getPosition(target);var mousePos=this.mouseCoords(ev);return{x:mousePos.x- docPos.x,y:mousePos.y- docPos.y};}
this.makeDraggable=function(item){if(!item)return;var self=this;item.onmousedown=function(ev){var target=getEventSource(ev);if(target.tagName=='INPUT'||target.tagName=='SELECT')return true;currenttable=self;self.dragObject=this;self.mouseOffset=self.getMouseOffset(this,ev);return false;}
item.style.cursor="move";}
this.findDropTargetRow=function(y){var rows=this.table.tBodies[0].rows;for(var i=0;i<rows.length;i++){var row=rows[i];var nodrop=row.getAttribute("NoDrop");if(nodrop==null||nodrop=="undefined"){var rowY=this.getPosition(row).y;var rowHeight=parseInt(row.offsetHeight)/2;if(row.offsetHeight==0){rowY=this.getPosition(row.firstChild).y;rowHeight=parseInt(row.firstChild.offsetHeight)/2;}
if((y>rowY- rowHeight)&&(y<(rowY+ rowHeight))){return row;}}}
return null;}}
if(/WebKit/i.test(navigator.userAgent)){var _timer=setInterval(function(){if(/loaded|complete/.test(document.readyState)){initialize();}},10);}
window.onload=initialize;