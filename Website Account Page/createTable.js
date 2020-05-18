//all sports icons
var sportIcons = ['account_images/soccer.png', 'account_images/frisbee.png', 'account_images/badminton.jpg',
              'account_images/hockey.jpg', 'account_images/volleyball.png', 'account_images/basketball.jpg'
              ,'account_images/baseball.png', 'account_images/football.jpg', 'account_images/beach volleyball.jpg'
              ,'account_images/swimming.png','account_images/tennis.png'];

//all sports names
var sportNames = ['Soccer', 'Ultimate Frisbee', 'Badminton',
              'Hockey', 'Volleyball', 'Basketball',
              'Baseball', 'Football', 'Beach Volleyball',
              'Swimming', 'Tennis'];
var randomNum = 0;


function initSports() {
  var otherSports = document.getElementById("sportsTable");

  for (var i = 0; i<sportNames.length; i++) {
    var currentRow = otherSports.insertRow(-1);

    var addCell = currentRow.insertCell(0);
    var iconCell = currentRow.insertCell(1);
    var nameCell = currentRow.insertCell(2);

    addCell.id = "addButton" + randomNum;
    randomNum++;

    addCell.innerHTML = "<button onclick='addToFav("+addCell.id+")'>ADD</button>";
    iconCell.innerHTML = "<img src='" + sportIcons[i] + "' style='width:50px; height:50px;'>";
    nameCell.innerHTML = sportNames[i];

  }

}

function addToFav(clicked_id) {
  var otherSports = document.getElementById("sportsTable");
  var mySports = document.getElementById("myTable");
  var rowToRemove;
  console.log(clicked_id);

  for (var i = 0, row; row = otherSports.rows[i]; i++) {
    for (var j = 0, col; col = row.cells[j]; j++) {
      if (col != null && col == clicked_id) {
        rowToRemove = row;
        otherSports.deleteRow(i);
        break;
      }
    }
  }
  console.log(rowToRemove.innerHTML);
  var row = mySports.insertRow(-1);
  row.innerHTML = rowToRemove.innerHTML;
  cell = row.insertCell(3);
  cell.innerHTML = "<select name='skill level'><option value='unsure' selected>Unsure</option><option value='novice'>Novice</option><option value='intermediate'>Intermediate</option><option value='Advanced'>Advanced</option><option value='expert'>Expert</option></select>";
  row.deleteCell(0);
  cell2 = row.insertCell(0);
  cell2.id = "removeButton" + randomNum;
  randomNum++;
  cell2.innerHTML = "<button onclick='addToOriginal("+cell2.id+")'>REMOVE</button>";

}

function addToOriginal(clicked_id) {
  var otherSports = document.getElementById("sportsTable");
  var mySports = document.getElementById("myTable");
  var rowToRemove;

  for (var i = 0, row; row = mySports.rows[i]; i++) {
    for (var j = 0, col; col = row.cells[j]; j++) {
      if (col != null && col == clicked_id) {
        rowToRemove = row;
        mySports.deleteRow(i);
        break;
      }
    }
  }

  var row = otherSports.insertRow(-1);
  row.innerHTML = rowToRemove.innerHTML;
  row.deleteCell(3);
  row.deleteCell(0);
  cell2 = row.insertCell(0);
  cell2.id = "addButton" + randomNum;
  randomNum++;
  cell2.innerHTML = "<button onclick='addToFav("+cell2.id+")'>ADD</button>";
}

