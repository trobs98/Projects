/**
*
* @brief Orchestrates what commands needs to be run and synthesizes speech.
* @author : Tyler Roberts, Pouya Langary, Seif Elmolla, Lionel Foxcroft
* Text commands are sent to orchestration to see which command needs to be run. When the command is 
* run, synthesizeSpeech takes in the response and translates it to speech to be said back to the user
*
*/     

#include "orchestration.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

	/**
	*
	* @author : Microsoft + changes by Tyler Roberts, Pouya Langary, Seif Elmolla, Lionel Foxcroft
	* @brief takes in text and says it via speakers.
	* 
	* Whatever response one of the commands returns is spoken back to the user.
	*
	*@param toSay the outputted response that one of the commands returned
	*@return nothing
	*
	*/         
void synthesizeSpeech(string toSay){
    // Creates an instance of a speech config with specified subscription key and service region.
    // Replace with your own subscription key and service region (e.g., "westus").
    auto config = SpeechConfig::FromSubscription("debac57d6c12416198985285425aabef", "westus");

    // Creates a speech synthesizer using the default speaker as audio output. The default spoken language is "en-us".
    auto synthesizer = SpeechSynthesizer::FromConfig(config);

    // Receive a text from console input and synthesize it to speaker.
    //cout << "Type some text that you want to speak..." << std::endl;
    //cout << "> ";
    std::string text = toSay;
    //getline(cin, text);

    auto result = synthesizer->SpeakTextAsync(text).get();

    // Checks result.
    if (result->Reason == ResultReason::SynthesizingAudioCompleted)
    {
        cout << "Speech synthesized to speaker for text [" << text << "]" << std::endl;
    }
    else if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);
        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            cout << "CANCELED: ErrorDetails=[" << cancellation->ErrorDetails << "]" << std::endl;
            cout << "CANCELED: Did you update the subscription info?" << std::endl;
        }
    }

    // This is to give some time for the speaker to finish playing back the audio
    cout << "Press enter to say a new command..." << std::endl;
    cin.get();
}

	/**
	*  @brief Constructor.
	*
	*  The constructor for the orchestration class which will create an empyt todo list.
	*
	*/
orchestration::orchestration(){
    myList = new todo();
}
      

//private function

	/**
	*  @brief adding a command to orchestration. 
	*
	*  This will send the inputted command text to one of the command files, specified by a keyword in the command.
	*  For example, the 'time' keyword will send the command text to the GetTime command file. 
	*	
	*  @param text the command that the user said
	*/        
void orchestration::addCommand(std::string text){
    toParse = text;
    vector<string> tokens = parseText(text);
    
    if(tokens.size() == 1){
            output = "Incorrect format of command.";
    }
    else if(tokens[1] == "time"){
        GetTime* time = new GetTime(text);
        output = time->GetOutput();
    }
    else if(tokens[1] == "day"){
        GetDate * date = new GetDate(text);
        output = date->getOutput();
    }
    else if(tokens[0] == "Add"){
        myList->addToList(tokens[1], (tokens[3] + " " + tokens[4] + " " + tokens[5].substr(0,tokens[5].size()-1)));
        output = myList->getOutput();
    }
    else if(tokens[3] == "To" && tokens[4] == "Do"){
        myList->getMyToDo();
        output = myList->getOutput();
    }
    else if(tokens[0] == "Mark"){
        myList->markCompleted(tokens[1]);
        output = myList->getOutput();
    }
    else if (tokens[0]== "Set"){
        Alarm *timer = new Alarm();
        
        vector<string>::iterator it = find(libraryNumbers.begin(), libraryNumbers.end(), tokens[3]);

        if(it != libraryNumbers.end() && distance(libraryNumbers.begin(), it) % 2 == 1){
            tokens[3] = libraryNumbers[distance(libraryNumbers.begin(), it) - 1];
        }
         
        timer->set_timer(stoi(tokens[3]), tokens[1]);
        output = tokens[1] + " has finished!";
    }
    else if (tokens[0] == "Evaluate") {
        Math * myMath = new Math();
        
        string betterCommand(text.size(), '0');
        betterCommand.erase(remove_copy(text.begin(), text.end(), betterCommand.begin(), ','), betterCommand.end());
    
        output = myMath->process_command(betterCommand.substr(0, betterCommand.size()-1));
    }
    else{
       output = "Incorrect format of question";  
    }
    
    setlocale(LC_ALL, "");
    synthesizeSpeech(output);
}
        
	/**
	*  @brief parses string into tokens. 
	*
	*  This will take in a string (inputted command text) and parse it into tokens, allowing us to find keywords.
	*
	*  @param text the command that the user said
	*/
std::vector<std::string> orchestration::parseText(std::string text){
    std::vector<std::string> tokens;

    istringstream iss(text);
    copy(istream_iterator<std::string>(iss), istream_iterator<std::string>(), back_inserter(tokens));

    return tokens;
}
    

