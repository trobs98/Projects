package subscribers;

import events.AbstractEvent;
import pubSubServer.SubscriptionManager;
import states.subscriber.StateFactory;
import states.subscriber.StateName;

/**
 * @author kkontog, ktsiouni, mgrigori an example concrete subscriber
 */
class ConcreteSubscriberA extends AbstractSubscriber {

	protected ConcreteSubscriberA(int id) {
		state = StateFactory.createState(StateName.defaultState);
		this.id = id;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see subscribers.ISubscriber#setState(states.subscriber.StateName)
	 */
	public void setState(StateName stateName) {
		state = StateFactory.createState(stateName);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see subscribers.ISubscriber#alert(events.AbstractEvent, java.lang.String)
	 */
	@Override
	public void alert(AbstractEvent event, String channelName) {
		System.out.println("Subscriber with ID: " + this.id + " is handling event with ID: " + event.getID()
				+ ", published on channel " + channelName);
		state.handleEvent(event, channelName);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see subscribers.ISubscriber#subscribe(java.lang.String)
	 */
	@Override
	public void subscribe(String channelName) {
		SubscriptionManager.getInstance().subscribe(channelName, this);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see subscribers.ISubscriber#unsubscribe(java.lang.String)
	 */
	@Override
	public void unsubscribe(String channelName) {
		SubscriptionManager.getInstance().unSubscribe(channelName, this);

	}

	/**
	 * 
	 * @see subscribers.ISubscriber#getID()
	 */
	@Override
	public int getID() {
		return this.id;
	}

}
