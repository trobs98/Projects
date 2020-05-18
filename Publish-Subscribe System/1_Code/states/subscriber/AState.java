package states.subscriber;

import events.AbstractEvent;

public class AState implements IState {

	public void handleEvent(AbstractEvent event, String channelName) {
		System.out.println("Event with ID: " + event.getID() + " handled on " + channelName);
	}

}
