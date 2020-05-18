package publishers;

import strategies.publisher.IStrategy;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class betaPub extends AbstractPublisher {

	protected ConcretePublisher betaPub;

	/**
	 * Creates an instance of ConcretePublisher class with given AbstractStrategy
	 * strategy and ID
	 * 
	 * @param strat
	 * @param id
	 */
	protected betaPub(IStrategy strat, int id) {
		betaPub = new ConcretePublisher(strat, id);
	}

}
