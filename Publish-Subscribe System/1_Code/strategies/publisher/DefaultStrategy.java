package strategies.publisher;

import java.util.ArrayList;

import events.AbstractEvent;
import events.EventFactory;
import events.EventMessage;
import events.EventType;
import pubSubServer.ChannelEventDispatcher;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class DefaultStrategy implements IStrategy {

	/**
	 * Strategy will create an arbitrary event if no event is passed through
	 * parameters Method will forward new event and List of channels to
	 * ChannelEventDispatcher
	 * 
	 * @see strategies.publisher.IStrategy#doPublish(int)
	 */
	public void doPublish(int publisherId) {
		ArrayList<String> channels = new ArrayList<>();
		channels.add("main");

		EventMessage message = new EventMessage("Default Message", "Default body");
		AbstractEvent event = EventFactory.createEvent(EventType.TypeA, publisherId, message);

		ChannelEventDispatcher.getInstance().postEvent(event, channels);

		System.out.println("Publisher with ID: " + publisherId + " publishes event " + event.getID());

	}

	/**
	 * Strategy will simply forward event and List of Channels to
	 * ChannelEventDispatcher
	 * 
	 * @see strategies.publisher.IStrategy#doPublish(AbstractEvent, int)
	 * 
	 */
	public void doPublish(AbstractEvent event, int publisherId) {
		ArrayList<String> channels = new ArrayList<>();
		channels.add("main");

		ChannelEventDispatcher.getInstance().postEvent(event, channels);
		System.out.println("Publisher with ID: " + publisherId + " publishes event " + event.getID());
	}

}