package subscribers;

/**
 * @author kkontog, ktsiouni, mgrigori an example concrete subscriber
 */
class GammaSubscriber extends AbstractSubscriber {

	protected ConcreteSubscriberA gamma;

	/**
	 * Class creates an instance of ConcreteSubscriber with specified ID
	 * 
	 * @param id
	 */
	protected GammaSubscriber(int id) {

		gamma = new ConcreteSubscriberA(id);

	}
}
