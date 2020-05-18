var infoClasses = ["username", "firstName", "lastName",
                "birthdate", "gender", "password", "email"];
var numOfInfos = 7;


function initInfo() {
  //******* WILL NEED TO CONNECT TO DB AND INITIALIZE USER ACCOUNT INFORMATION BASED ON WHAT'S IN DB ******
  //initialize middle grid info and left grid icon info
}


//Allows the user to change their information when they click the edit button
function editInfo() {
  var list = document.getElementById("infoList");//list of user information
  var info = list.getElementsByTagName("dd");//list of all the HTML elements between the dd tags in the list 'list'
  var submit = document.getElementById("infoSubmit"); //location where update button is added
  var editButton = document.getElementById("infoEdit"); //location where edit button is

  //removes the edit button
  editButton.parentNode.removeChild(editButton);
  //adds an update button to be clicked when user is done changing their information
  submit.innerHTML = "<button type='submit' id='submitInfoButton' onclick='updateInfo()' >UPDATE</button>";

  //loops through the HTML elements from the variable info
  for (var i = 0; i < numOfInfos; i++) {

    //type = each <dd> ... </dd> tag
    var type = info[i];
    var currentHTML = type.innerHTML;

    //adds some sort of input tag depending on the class name to allow the user to update their information
          //Doesn't allow the user to change username (might make database too hectic)
    if (type.className == "firstName") {
      type.innerHTML = "<input type='text' class='firstName' value='" + currentHTML + "' maxLength='20'></input>";
    }

    else if(type.className == "lastName") {
      type.innerHTML = "<input type='text' class='lastName' value='" + currentHTML + "' maxLength='20'></input>";
    }

    else if (type.className == "birthdate") {
      type.innerHTML = "<input type='date' class='birthdate' value='" + currentHTML + "'></input>";
    }

    else if (type.className == "gender") {
      //not sure how to select something from dropdown based on what text is originally in users info
      //so just used if statements depending on what the text says
      if (type.innerHTML == "Male") {
        type.innerHTML = "<select name='Gender' class='gender'> <option value='Male' selected>Male</option> <option value='Female'>Female</option> </select>";
      }
      else {
        type.innerHTML = "<select name='Gender' class='gender'> <option value='Male'>Male</option> <option value='Female' selected>Female</option> </select>";
      }
    }

    else if (type.className == "password"){
      type.innerHTML = "<input type='password' class='password' value='" + currentHTML + "' maxLength='20'></input>";
    }

    else if (type.className == "email") {
      type.innerHTML = "<input type='email' class='email' value='" + currentHTML + "' maxLength='50'></input>"
    }

    else {
      continue;
    }
  }
}


//Updates the info after the user has already clicked edit
function updateInfo() {
  var list = document.getElementById("infoList");//list of users information
  var items = list.getElementsByTagName("dd");//list of all HTML elements between dd tags in the list 'list'
  var submitButton = document.getElementById("submitInfoButton");//place where update button is
  var edit = document.getElementById("infoEditArea");//place where we'll add the edit button back

  //Verification loop that makes sure what the user has entered is valid
  for (var i = 1; i < numOfInfos; i++) {
    var info = items[i].getElementsByClassName(infoClasses[i]);
    var classType = items[i].className;
    var value = info[0].value;

    //makes sure the fields are not empty
    if (value == "") {
      alert("ERROR: Cannot leave fields blank.");
      return;
    }
      //makes sure the fields do not contain spaces
    else if (/\s+/.test(value) == true) {
      alert("ERROR: Field should not contain space characters.");
      return;
    }
    else {

      //verifies first name and last name
      if (classType == "firstName" || classType == "lastName") {
        var variable = /^[a-zA-Z]+$/.test(value);

        if (variable == true) {
          continue;
        }
        else {
          alert("ERROR: Name must contain only letters.");
          return;
        }
      }

        //verifies birthdate
      else if (classType == "birthdate") {

         //todays date
        var today = new Date();
        var currentYear = today.getFullYear();
        var currentMonth = today.getMonth() + 1;
        var currentDay = today.getDate();

        //users birthdate
        var userYear = parseInt(value.substr(0, 4));
        var userMonth = parseInt(value.charAt(5) + value.charAt(6));
        var userDay = parseInt(value.substr(8, 10));

        //users age
        var age = (currentYear - userYear);
        if ((currentMonth - userMonth) < 0) {
          age--;
        }
        else {
          if ((currentMonth == userMonth) && ((currentDay - userDay) < 0)) {
            age--;
          }
        }

        //makes sure user is 18 years or older
        if (age >= 18) {
          continue;
        }
        else {
          alert("ERROR: Must be 18 years or older.");
          return;
        }
      }

      else if (classType == "password") {
        if (value.length < 8) {
          alert("ERROR: Password must be 8 characters or longer.");
          return;
        }
      }

      //NOT REALLY SURE WHAT TO DO FOR EMAIL
      /* else if (classType == "email"){

      }*/
    }
  }

  //allows you to change the name displayed in icon/avatar (left) grid section
  var iconFirstName = document.getElementById("iconFirst");
  var iconLastName = document.getElementById("iconLast");

  //loops through the input tags and replaces the new info the user added to their account 
  for (var i = 1; i < numOfInfos; i++) {
    var info = items[i].getElementsByClassName(infoClasses[i]);
    var value = info[0].value;

    if (infoClasses[i] == "password") {
      items[i].innerHTML = "************";
    }
    else if (infoClasses[i] == "firstName") {
      items[i].innerHTML = value;
      iconFirstName.innerHTML = value;
    }
    else if (infoClasses[i] == "lastName") {
      items[i].innerHTML = value;
      iconLastName.innerHTML = value;
    }
    else {
      items[i].innerHTML = value;
    }
  }

  //removes update button
  submitButton.parentNode.removeChild(submitButton);
  //adds edit button back
  edit.innerHTML = "<button type='button' id='infoEdit' onclick='editInfo()'>Edit</button>";

  //******* WILL NEED TO UPDATE THE DATABASE TO USERS NEW INFO ONCE WE FIGURE OUT HOW ******
}

function editIcon() {
  var editArea = document.getElementById("inputIcon");
  editArea.innerHTML = "Add Image (must be .jpg or .png) <br><input type='file' name='icon' id='newPic' accept='image/*' onchange='validatePic(this)'></input>";
}

function validatePic(file) {
  var avatorLoc = document.getElementById("avatar");

  if (file.files && file.files[0]) {
    var reader = new FileReader();
    reader.onload = function (e) {
      avatorLoc.setAttribute("src", e.target.result);
    }
    reader.readAsDataURL(file.files[0]);
  }
  var editArea = document.getElementById("inputIcon");
  editArea.innerHTML = "<button type='button' id='iconEdit' onclick='editIcon()'>Update Icon</button>";

  //******* WILL NEED TO UPDATE THE DATABASE TO USERS NEW INFO ONCE WE FIGURE OUT HOW ******
}
