package subscribers;

import states.subscriber.StateName;

/**
 * @author kkontog, ktsiouni, mgrigori
 *  
 */
/**
 * @author kkontog, ktsiouni, mgrigori creates new {@link AbstractSubscriber}
 *         objects contributes to the State design pattern implements the
 *         FactoryMethod design pattern
 */
public class SubscriberFactory {

	/**
	 * creates a new {@link AbstractSubscriber} using an entry from the
	 * {@link SubscriberType} enumeration
	 * 
	 * @param subscriberType
	 *            a value from the {@link SubscriberType} enumeration specifying the
	 *            type of Subscriber to be created
	 * @return the newly created {@link AbstractSubscriber} instance
	 */
	public static AbstractSubscriber createSubscriber(SubscriberType subscriberType, StateName stateName) {
		AbstractSubscriber CSA = null;
		switch (subscriberType) {
		case alpha:
			CSA = new AlphaSubscriber(SubscriberIDMaker.getNewSubID()).alpha;
			CSA.setState(stateName);
			System.out.println("Subscriber with ID: " + CSA.getID() + " is in state " + stateName);
			return CSA;
		case beta:
			CSA = new BetaSubscriber(SubscriberIDMaker.getNewSubID()).beta;
			CSA.setState(stateName);
			System.out.println("Subscriber with ID: " + CSA.getID() + " is in state " + stateName);
			return CSA;
		case gamma:
			CSA = new GammaSubscriber(SubscriberIDMaker.getNewSubID()).gamma;
			CSA.setState(stateName);
			System.out.println("Subscriber with ID: " + CSA.getID() + " is in state " + stateName);
			return CSA;
		default: // Double check if we can use alpha as the default
			CSA = new AlphaSubscriber(SubscriberIDMaker.getNewSubID()).alpha;
			CSA.setState(stateName);
			System.out.println("Default subscriber used, AlphaSubscriber created");
			System.out.println("Subscriber with ID: " + CSA.getID() + " is in state " + stateName);
			return CSA;
		}
	}

}
