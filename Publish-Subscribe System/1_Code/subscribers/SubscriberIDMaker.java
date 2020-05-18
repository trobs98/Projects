package subscribers;

/**
 * 
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */
public class SubscriberIDMaker {

	private static int subUIDs = 0;

	/**
	 * @return the next number of type {@link int}in the series of UID for the
	 *         AbstractSubscriber derived classes
	 * @return
	 */
	protected static int getNewSubID() {
		return subUIDs++;
	}

}
