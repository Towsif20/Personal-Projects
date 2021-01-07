const size = 6;
const INF = 100000;
const timeLimit = 5000;
var humanvshuman = false;
var finished = false;

pieceSquareTable =
    [

        [-80, -25, -20, -20, -20, -20, -25, -80],
        [-25, 10, 10, 10, 10, 10, 10, -25],
        [-20, 10, 25, 25, 25, 25, 10, -20],
        [-20, 10, 25, 50, 50, 25, 10, -20],
        [-20, 10, 25, 50, 50, 25, 10, -20],
        [-20, 10, 25, 25, 25, 25, 10, -20],
        [-25, 10, 10, 10, 10, 10, 10, -25],
        [-80, -25, -20, -20, -20, -20, -25, -80]

    ];

var whiteList = [];
var blacklist = [];
var allowed = [];
var bg = [];
var selected = null;
var selected2 = null;

const WHITE = 1;
const BLACK = 2;

var turn = BLACK;

function init()
{
    var board = "";
    for (var i = 0; i < size; i++)
    {
        board += "<div id = " + i + ">";

        for (var j = 0; j < size; j++)
        {
            board += '<span ><textarea id = "' + i + j + '" onClick = "F(this.id)" readonly>' + '</textarea></span>';
        }

        board += "</div>";

    }

    document.getElementById("turn").innerHTML = "BLACK";
    document.getElementById("board").innerHTML = board;

    for (var i = 0; i < size; i++)
    {

        for (var j = 0; j < size; j++)
        {
            var element = document.getElementById(i.toString() + j.toString());
            element.classList.add('button');

            if ((i + j) % 2 == 0)
            {
                element.style.backgroundColor = "#E7BA84";
            }
            else
            {
                element.style.backgroundColor = "#DE9A42";
            }
        }

    }
}



function initMarkers()
{
    for (var i = 0; i < size - 2; i++)
    {
        whiteList[i] = (i + 1) + '0';
        blacklist[i] = '0' + (i + 1);
        //whiteList.add((i + 1).toString() + (size - 1).toString())
    }

    var len = whiteList.length;

    for (var i = 0; i < size - 2; i++)
    {
        whiteList[i + len] = (i + 1).toString() + (size - 1).toString();
        blacklist[i + len] = (size - 1).toString() + (i + 1).toString();
    }

}

// console.log(whiteList);
// console.log(blacklist);

function resetBoard()
{
    var x = document.getElementsByClassName("white");

    for (var i = 0; i < x.length; i++)
    {
        x[i].value = "";
    }

    x = document.getElementsByClassName("black");

    for (var i = 0; i < x.length; i++)
    {
        x[i].value = "";
    }
}

function updateBoard()
{
    resetBoard();

    len = whiteList.length;

    for (var i = 0; i < len; i++)
    {
        var element = document.getElementById(whiteList[i]);
        element.value = "O";

        element.classList.remove("black");
        element.classList.add("white");
    }

    len = blacklist.length;

    for (var i = 0; i < len; i++)
    {
        var element = document.getElementById(blacklist[i]);
        element.value = "O";

        element.classList.remove("white");
        element.classList.add("black");

    }

}


function selectFirst(myList, id)
{

    for (var i = 0; i < myList.length; i++)
    {
        if (myList[i] == id)
        {
            selected = id;

            document.getElementById("warning").innerHTML = "selected " + selected + "<br>Now select a permissible block";

            getPermissibleBlocks(id);

            //console.log(allowed);

            for (var j = 0; j < allowed.length; j++)
            {
                bg[j] = document.getElementById(allowed[j]).style.backgroundColor;
                document.getElementById(allowed[j]).style.backgroundColor = "aqua";
            }

            if (allowed.length == 0)
            {
                selected = selected2 = null;
                document.getElementById("warning").innerHTML = "selected " + selected + "<br>No allowed blocks for this, select a new one";
            }



            break;
        }

    }
}

function selectSecond(myList, id)
{
    if (myList == whiteList)
        opponentList = blacklist;

    else
        opponentList = whiteList;

    if (!(inList(allowed, id)))
    {

        return;
    }
    selected2 = id;

    for (var i = 0; i < myList.length; i++)
    {
        if (myList[i] == selected)
        {
            var flag = true;

            for (var j = 0; j < myList.length; j++)
            {
                if (myList[j] == selected2)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                for (var j = 0; j < opponentList.length; j++)
                {
                    if (opponentList[j] == selected2)
                    {
                        opponentList.splice(j, 1);
                        break;
                    }
                }
                myList[i] = selected2;

            }

        }
    }

    for (var i = 0; i < allowed.length; i++)
    {
        document.getElementById(allowed[i]).style.backgroundColor = bg[i];
    }

    selected = selected2 = null;
    allowed = [];
    bg = [];

    var result = checkWinner(whiteList);
    //console.log("white wins: " + result);

    changeMove();
}

function getPermissibleInRow(id)
{
    if (turn == WHITE)
    {
        myList = whiteList;
        opponentList = blacklist;
    }
    else
    {
        myList = blacklist;
        opponentList = whiteList;
    }

    var row = id[0];

    var count = 0;

    for (var i = 0; i < size; i++)
    {
        var rowID = row + i.toString();

        if (inList(whiteList, rowID) || inList(blacklist, rowID))
            count++;
    }

    var t1 = parseInt(id[1]) + count;
    var t2 = parseInt(id[1]) - count;

    // console.log("t1 = " + t1);
    // console.log("t2 = " + t2);

    var p1 = null;
    var p2 = null;

    if (t1 < size)
    {
        var r = parseInt(id[1]);

        for (var i = r + 1; i < r + count; i++)
        {
            var rID = row + i.toString();

            if (inList(opponentList, rID))
            {
                flag = true;
                break;

            }
        }

        if (!flag)
            p1 = row + t1.toString();


    }

    if (t2 >= 0)
    {
        var r = parseInt(id[1]);

        var flag = false;

        for (var i = r - 1; i > r - count; i--)
        {
            var rID = row + i.toString();

            if (inList(opponentList, rID))
            {
                flag = true;
            }

        }

        if (!flag)
            p2 = row + t2.toString();
    }


    if (!inList(myList, p1) && p1 != null)
        allowed.push(p1)

    if (!inList(myList, p2) && p2 != null)
        allowed.push(p2)

    //console.log(allowed);

}
function getPermissibleInColumn(id)
{
    if (turn == WHITE)
    {
        myList = whiteList;
        opponentList = blacklist;
    }
    else
    {
        myList = blacklist;
        opponentList = whiteList;
    }

    var column = id[1];

    var count = 0;

    for (var i = 0; i < size; i++)
    {
        var colID = i.toString() + column;;

        if (inList(whiteList, colID) || inList(blacklist, colID))
            count++;
    }

    var t1 = parseInt(id[0]) + count;
    var t2 = parseInt(id[0]) - count;

    // console.log("t1 = " + t1);
    // console.log("t2 = " + t2);
    var p1 = null;
    var p2 = null;

    if (t1 < size)
    {
        var c = parseInt(id[0]);

        var flag = false;

        for (var i = c + 1; i < c + count; i++)
        {
            var cID = i.toString() + column;

            if (inList(opponentList, cID))
            {
                flag = true;
                break;
            }

        }

        if (!flag)
        {
            p1 = t1.toString() + column;
        }
    }

    if (t2 >= 0)
    {
        var c = parseInt(id[0]);
        var flag = false;

        for (var i = c - 1; i > c - count; i--)
        {
            var cID = i.toString() + column;

            if (inList(opponentList, cID))
            {
                flag = true;
                break;
            }
        }

        if (!flag)
        {

            p2 = t2.toString() + column;
        }
    }

    if (!inList(myList, p1) && p1 != null)
    {
        allowed.push(p1)
    }


    if (!inList(myList, p2) && p2 != null)
        allowed.push(p2)

    //console.log(allowed);
}
function getPermissibleDiagonal(id)
{
    if (turn == WHITE)
    {
        myList = whiteList;
        opponentList = blacklist;
    }
    else
    {
        myList = blacklist;
        opponentList = whiteList;
    }

    var row = id[0];
    var column = id[1];

    var r = parseInt(row);
    var c = parseInt(column);
    var temp = [];
    var count1 = 0;
    var count2 = 0;

    while (r >= 0 && c >= 0)
    {
        var index = r.toString() + c.toString();

        if (inList(whiteList, index) || inList(blacklist, index))
            count1++;

        r--;
        c--;

    }

    r = parseInt(row);
    c = parseInt(column);

    while (r < size && c < size)
    {
        var index = r.toString() + c.toString();

        if (inList(whiteList, index) || inList(blacklist, index))
            count1++;

        r++;
        c++;

    }

    count1--;



    r = parseInt(row);
    c = parseInt(column);





    var t1 = r + count1;
    var t2 = r - count1;
    var t3 = c + count1;
    var t4 = c - count1;

    var p1 = null;
    var p2 = null;
    var p3 = null;
    var p4 = null;

    if (t1 < size && t3 < size)
    {
        var index = t1.toString() + t3.toString();
        var flag = false;

        var i = r + 1;
        var j = c + 1;

        while (i < t1 && j < t3)
        {
            var tid = i.toString() + j.toString();

            if (inList(opponentList, tid))
            {
                flag = true;
                break;
            }
            i++;
            j++;
        }

        if (!flag)
            p1 = index;
    }

    if (!inList(myList, p1) && p1 != null)
        allowed.push(p1);







    if (t2 >= 0 && t4 >= 0)
    {
        var index = t2.toString() + t4.toString();
        var flag = false;

        var i = r - 1;
        var j = c - 1;

        while (i > t2 && j > t4)
        {
            var tid = i.toString() + j.toString();

            if (inList(opponentList, tid))
            {
                flag = true;
                break;
            }
            i--;
            j--;
        }

        if (!flag)
            p2 = index;
    }

    if (!inList(myList, p2) && p2 != null)
        allowed.push(p2);





    //copy here

    // var t1 = r + count1;
    // var t2 = r - count1;
    // var t3 = c + count1;
    // var t4 = c - count1;





    r = parseInt(row);
    c = parseInt(column);

    while (r < size && c >= 0)
    {
        var index = r.toString() + c.toString();

        if (inList(whiteList, index) || inList(blacklist, index))
            count2++;

        r++;
        c--;

    }

    r = parseInt(row);
    c = parseInt(column);

    while (r >= 0 && c < size)
    {
        var index = r.toString() + c.toString();

        if (inList(whiteList, index) || inList(blacklist, index))
            count2++;

        r--;
        c++;

    }

    count2--;



    r = parseInt(row);
    c = parseInt(column);





    t1 = r + count2;
    t2 = r - count2;
    t3 = c + count2;
    t4 = c - count2;

    // var p1 = null;
    // var p2 = null;
    // var p3 = null;
    // var p4 = null;

    if (t1 < size && t4 >= 0)
    {
        var index = t1.toString() + t4.toString();
        var flag = false;

        var i = r + 1;
        var j = c - 1;

        while (i < t1 && j > t4)
        {
            var tid = i.toString() + j.toString();

            if (inList(opponentList, tid))
            {
                flag = true;
                break;
            }
            i++;
            j--;
        }

        if (!flag)
            p3 = index;
    }

    if (!inList(myList, p3) && p3 != null)
        allowed.push(p3);




    r = parseInt(row);
    c = parseInt(column);

    if (t2 >= 0 && t3 < size)
    {
        var index = t2.toString() + t3.toString();
        var flag = false;

        var i = r - 1;
        var j = c + 1;

        while (i > t2 && j < t3)
        {
            var tid = i.toString() + j.toString();

            if (inList(opponentList, tid))
            {
                flag = true;
                break;
            }
            i--;
            j++;
        }

        if (!flag)
            p4 = index;
    }

    if (!inList(myList, p4) && p4 != null)
        allowed.push(p4);


}

function getPermissibleBlocks(id)
{
    allowed = [];

    getPermissibleInRow(id);
    getPermissibleInColumn(id);
    getPermissibleDiagonal(id);
    //allowed.concat(getPermissibleDiagonal(id));

    //return allowed;
}



function changeMove()
{
    if (turn == WHITE)
    {
        turn = BLACK;
        s = "BLACK";
    }
    else
    {
        turn = WHITE;
        s = "WHITE";
    }

    updateBoard();

    document.getElementById("turn").innerHTML = s;
    document.getElementById("warning").innerHTML = "select a " + s + " block";
}

var traverseList = [];

function checkConnected(myList, id)
{

    if (inList(traverseList, id))
        return;

    traverseList.push(id);

    var index0 = parseInt(id[0]);
    var index1 = parseInt(id[1]);

    var temp = [];

    temp.push((index0 - 1).toString() + (index1 - 1).toString());
    temp.push((index0 - 1).toString() + index1.toString());
    temp.push((index0 - 1).toString() + (index1 + 1).toString());

    temp.push((index0).toString() + (index1 - 1).toString());
    temp.push((index0).toString() + (index1 + 1).toString());

    temp.push((index0 + 1).toString() + index1.toString());
    temp.push((index0 + 1).toString() + (index1 + 1).toString());
    temp.push((index0 + 1).toString() + (index1 - 1).toString());

    for (var i = 0; i < temp.length; i++)
    {
        if (inList(myList, temp[i]))
        {
            checkConnected(myList, temp[i]);
        }
    }

    //console.log(traverseList);
}

function inList(myList, id)
{
    for (var i = 0; i < myList.length; i++)
    {
        if (myList[i] == id)
            return true;
    }

    return false;
}

function checkWinner(myList)
{
    checkConnected(myList, myList[0]);

    var flag = false;

    if (traverseList.length == myList.length)
        flag = true;

    //console.log(traverseList);

    traverseList.splice(0, traverseList.length);

    return flag;
}

function F(id)
{
    if (finished)
        return;

    if (humanvshuman)
    {
        if (turn == WHITE)
        {
            if (selected == null)
            {
                selectFirst(whiteList, id);
            }
            else
            {
                selectSecond(whiteList, id);



            }

        }

        else
        {
            if (selected == null)
            {
                selectFirst(blacklist, id);

            }
            else
            {
                selectSecond(blacklist, id);

                console.log("black done");

            }
        }

    }

    else
    {
        if (selected == null)
        {
            selectFirst(blacklist, id);

        }
        else
        {
            selectSecond(blacklist, id);

            var result = checkWinner(blacklist);

            if (result)
            {
                console.log("black wins");
                finished = true;
                return;
            }

            console.log("black done");

            var state = new State(whiteList, blacklist);
            state.AlphaBetaSearch();

            result = checkWinner(whiteList);

            if (result)
            {
                console.log("white wins");
                finished = true;
            }

        }
    }


}

var depth = 0;
var t0;
var t1;

class State
{
    constructor(whitePositions, blackPositions)
    {
        this.whitePositions = [];
        this.blackPositions = [];
        for (var i = 0; i < whitePositions.length; i++)
        {
            this.whitePositions[i] = whitePositions[i];
        }
        for (var i = 0; i < blackPositions.length; i++)
        {
            this.blackPositions[i] = blackPositions[i];
        }

        this.children = [];
        this.nextMove = null;
    }

    AreaUtility()
    {
        if (turn == WHITE)
        {
            var minRow = INF;
            var maxRow = -INF;
            var minCol = INF;
            var maxCol = -INF;

            for (var i = 0; i < this.whitePositions.length; i++)
            {
                var row = parseInt(this.whitePositions[i][0]);
                minRow = Math.min(row, minRow);
                maxRow = Math.max(row, maxRow);

                var col = parseInt(this.whitePositions[i][1]);
                minCol = Math.min(col, minCol);
                maxCol = Math.max(col, maxCol);
            }

            var area = (maxCol - minCol) * (maxRow - minRow);

            return 1000 / area;
        }

        else
        {
            var minRow = INF;
            var maxRow = -INF;
            var minCol = INF;
            var maxCol = -INF;

            for (var i = 0; i < this.blackPositions.length; i++)
            {
                var row = parseInt(this.blackPositions[i][0]);
                minRow = Math.min(row, minRow);
                maxRow = Math.max(row, maxRow);

                var col = parseInt(this.blackPositions[i][1]);
                minCol = Math.min(col, minCol);
                maxCol = Math.max(col, maxCol);
            }

            var area = (maxCol - minCol) * (maxRow - minRow);

            return 1000 / area;
        }
    }

    piece()
    {
        var whiteScore = 0;
        var blackScore = 0;

        for (var i = 0; i < size; i++)
        {
            for (var j = 0; j < size; j++)
            {
                var id = i.toString() + j.toString();
                // var id = (i + 1).toString() + (j + 1).toString();

                if (inList(this.whitePositions, id))
                {
                    if (size == 8)
                        whiteScore += pieceSquareTable[i][j];
                    else
                        whiteScore += pieceSquareTable[i + 1][j + 1];
                }
                else if (inList(this.blackPositions, id))
                {
                    if (size == 8)
                        blackScore += pieceSquareTable[i][j];
                    else
                        blackScore += pieceSquareTable[i + 1][j + 1];
                }
            }
        }

        if (turn == WHITE)
            return whiteScore;
        else
            return blackScore;

    }

    utilityFunction()
    {
        //return this.AreaUtility();
        return this.piece();

    }

    // produceChildren()
    // {
    //     this.children = [];
    //     var opponentList = [];
    //     var myList = [];

    //     if (turn == WHITE)
    //     {
    //         myList = this.whitePositions;
    //         opponentList = this.blackPositions;
    //     }
    //     else
    //     {
    //         opponentList = this.whitePositions;
    //         myList = this.blackPositions;
    //     }

    //     for (var i = 0; i < myList.length; i++)
    //     {
    //         selectFirst(myList, myList[i]);

    //         getPermissibleBlocks(myList[i]);

    //         for (var j = 0; j < allowed.length; j++)
    //         {
    //             var state = null;
    //             selectSecond(myList, allowed[j]);
    //             if (turn == WHITE)
    //                 state = new State(myList, opponentList);
    //             else
    //                 state = new State(opponentList, myList);
    //             selected2 = null;

    //             this.children.push(state);
    //         }

    //         allowed = [];
    //     }
    // }

    produceChildren2()
    {
        var opponentList = [];
        var myList = [];

        if (turn == WHITE)
        {
            myList = this.whitePositions;
            opponentList = this.blackPositions;
        }
        else
        {
            opponentList = this.whitePositions;
            myList = this.blackPositions;
        }

        for (var i = 0; i < myList.length; i++)
        {
            console.log("myList[i] = " + myList[i]);
            getPermissibleBlocks(myList[i]);
            console.log("allowed = \n" + allowed);

            for (var j = 0; j < allowed.length; j++)
            {

                var tempList = [];
                var tempList2 = [];
                for (var k = 0; k < myList.length; k++)
                {
                    tempList[k] = myList[k];
                }

                for (var k = 0; k < opponentList.length; k++)
                {
                    tempList2[k] = opponentList[k];
                }

                for (var k = 0; k < tempList2.length; k++)
                {
                    if (tempList2[k] == allowed[j])
                    {
                        tempList2.splice(k, 1);
                    }
                }

                tempList[i] = allowed[j];

                if (turn == WHITE)
                    this.children.push(new State(tempList, tempList2));
                else
                    this.children.push(new State(tempList2, tempList));


            }

            allowed = [];
        }
    }

    AlphaBetaSearch()
    {
        t0 = performance.now();

        var v = this.Max_Value(-INF, INF);

        //console.log(this.nextMove);

        blacklist = [];
        whiteList = [];

        for (var i = 0; i < this.nextMove.blackPositions.length; i++)
        {
            blacklist[i] = this.nextMove.blackPositions[i];
        }

        for (var i = 0; i < this.nextMove.whitePositions.length; i++)
        {
            whiteList[i] = this.nextMove.whitePositions[i];
        }


        changeMove();
        //this.update();
    }

    Max_Value(a, b)
    {
        t1 = performance.now();
        if (t1 - t0 > timeLimit)
            return this.utilityFunction();

        turn = WHITE;
        var test = this.terminalTest(this.whitePositions);
        if (test)
            return this.utilityFunction();

        this.produceChildren2();

        console.log(this.children);
        //console.log(this.children);

        var v = -INF;
        for (var i = 0; i < this.children.length; i++)
        {
            var child = this.children[i];
            var min = child.Min_Value(a, b);

            if (v < min)
            {
                v = min;

                this.nextMove = new State(this.whitePositions, this.blackPositions);

                for (var j = 0; j < child.whitePositions.length; j++)
                {
                    this.nextMove.whitePositions[j] = child.whitePositions[j];
                }

                for (var j = 0; j < child.blackPositions.length; j++)
                {
                    this.nextMove.blackPositions[j] = child.blackPositions[j];
                }
                //this.nextMove.blackPositions = child.blackPositions;
                //this.nextMove.whitePositions = child.whitePositions;
            }

            if (v >= b)
                return v;

            a = Math.max(a, v);
        }

        return v;

    }

    Min_Value(a, b)
    {
        t1 = performance.now();
        if (t1 - t0 > timeLimit)
            return this.utilityFunction();

        turn = BLACK;
        var test = this.terminalTest(this.blackPositions);

        if (test)
            return this.utilityFunction();

        this.produceChildren2();

        var v = INF;

        for (var i = 0; i < this.children.length; i++)
        {
            v = Math.min(v, this.children[i].Max_Value(a, b));

            if (v <= a)
                return v;

            b = Math.min(b, v);
        }

        return v;
    }

    terminalTest(myList)
    {
        return checkWinner(myList);
    }

    getWhitePositions()
    {
        return this.whitePositions;
    }

    getBlackPositions()
    {
        return this.blackPositions;
    }

    update()
    {
        whiteList = this.whitePositions;
        blacklist = this.blackPositions;

        updateBoard();
    }
}


init();
initMarkers();
updateBoard();

// whiteList[]



//console.log(root.getBlackPositions());

//root.blackPositions[3] = "44";

//root.update();
//console.log(blacklist);
