package publishers;

import strategies.publisher.IStrategy;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class alphaPub extends AbstractPublisher {

	protected ConcretePublisher alphaPub;

	/**
	 * Creates an instance of ConcretePublisher class with given AbstractStrategy
	 * strategy and ID
	 * 
	 * @param strat
	 * @param id
	 */
	protected alphaPub(IStrategy strat, int id) {
		alphaPub = new ConcretePublisher(strat, id);
	}

}