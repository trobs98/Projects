package subscribers;

/**
 * @author kkontog, ktsiouni, mgrigori an example concrete subscriber
 */
class AlphaSubscriber extends AbstractSubscriber {

	protected ConcreteSubscriberA alpha;

	/**
	 * Class creates an instance of ConcreteSubscriber with specified ID
	 * 
	 * @param id
	 */
	protected AlphaSubscriber(int id) {
		alpha = new ConcreteSubscriberA(id);
	}
}
