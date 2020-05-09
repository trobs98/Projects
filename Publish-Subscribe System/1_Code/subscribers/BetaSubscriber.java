package subscribers;

/**
 * @author kkontog, ktsiouni, mgrigori an example concrete subscriber
 */
class BetaSubscriber extends AbstractSubscriber {

	protected ConcreteSubscriberA beta;

	/**
	 * Class creates an instance of ConcreteSubscriber with specified ID
	 * 
	 * @param id
	 */
	protected BetaSubscriber(int id) {

		beta = new ConcreteSubscriberA(id);

	}
}
