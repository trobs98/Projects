package publishers;

import strategies.publisher.IStrategy;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class deltaPub extends AbstractPublisher {

	protected ConcretePublisher deltaPub;

	/**
	 * Creates an instance of ConcretePublisher class with given AbstractStrategy
	 * strategy and ID
	 * 
	 * @param strat
	 * @param id
	 */
	protected deltaPub(IStrategy strat, int id) {
		deltaPub = new ConcretePublisher(strat, id);
	}

}