
package pubSubServer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import subscribers.AbstractSubscriber;

/**
 * @author kkontog, ktsiouni, mgrigori MUST Implements the Singleton design
 *         pattern Class that acts as an access control module that allows for
 *         the blocking and unblocking of specific subscribers for specific
 *         channels
 * 
 */
public class ChannelAccessControl {
	private static ChannelAccessControl single_instance = null;

	public static ChannelAccessControl getInstance() {
		if (single_instance == null)
			single_instance = new ChannelAccessControl();
		return single_instance;
	}

	Map<String, List<AbstractSubscriber>> blackList = new HashMap<>();

	/**
	 * 
	 * blocks the provided subscriber from accessing the designated channel
	 * 
	 * @param subscriber
	 *            an instance of any implementation of {@link AbstractSubscriber}
	 * @param channelName
	 *            a String value representing a valid channel name
	 */
	public void blockSubcriber(AbstractSubscriber subscriber, String channelName) {

		List<AbstractSubscriber> blockedSubscribers = blackList.getOrDefault(channelName,
				new ArrayList<AbstractSubscriber>());
		if (!blockedSubscribers.contains(subscriber)){
			blockedSubscribers.add(subscriber);
			blackList.put(channelName, blockedSubscribers);
			System.out.println("Subsriber with ID: " + subscriber.getID() + " is blocked on channel " + channelName);
		}
		else {
			System.out.println("Subscriber "+ subscriber.getID() + " already blocked on " + channelName);
		}
	}

	/**
	 * unblocks the provided subscriber from accessing the designated channel
	 * 
	 * @param subscriber
	 *            an instance of any implementation of {@link AbstractSubscriber}
	 * @param channelName
	 *            a String value representing a valid channel name
	 */
	public void unBlockSubscriber(AbstractSubscriber subscriber, String channelName) {

		List<AbstractSubscriber> blockedSubscribers;
		if ((blockedSubscribers = blackList.get(channelName)) == null)
			return;
		if (blockedSubscribers.contains(subscriber)){
			blockedSubscribers.remove(subscriber);
			System.out.println("Subsriber with ID: " + subscriber.getID() + " is unblocked on channel " + channelName);
		}
		else {
			System.out.println("Subscriber " + subscriber.getID() + " not already blocked.");
		}
	}

	/**
	 * checks if the provided subscriber is blocked from accessing the specified
	 * channel
	 * 
	 * @param subscriber
	 *            an instance of any implementation of {@link AbstractSubscriber}
	 * @param channelName
	 *            a String value representing a valid channel name
	 * @return true if blocked false otherwise
	 */
	public boolean checkIfBlocked(AbstractSubscriber subscriber, String channelName) {

		List<AbstractSubscriber> blockedSubscribers;
		if ((blockedSubscribers = blackList.get(channelName)) == null)
			return false;
		return (blockedSubscribers.contains(subscriber));
	}

}
