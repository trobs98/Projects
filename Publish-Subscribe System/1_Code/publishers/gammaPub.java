package publishers;

import strategies.publisher.IStrategy;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class gammaPub extends AbstractPublisher {

	protected ConcretePublisher gammaPub;

	/**
	 * Creates an instance of ConcretePublisher class with given AbstractStrategy
	 * strategy and ID
	 * 
	 * @param strat
	 * @param id
	 */
	protected gammaPub(IStrategy strat, int id) {
		gammaPub = new ConcretePublisher(strat, id);
	}

}