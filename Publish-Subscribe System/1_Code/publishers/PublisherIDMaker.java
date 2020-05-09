package publishers;

/**
 *
 * @author Dinushan Dayarathna, Pouya Langaray, Sarah Clowes-Walker, Seif
 *         Elmolla, Tyler Roberts
 *
 */

public class PublisherIDMaker {
	private static int pubUIDs = 0;

	/**
	 * @return the next number of type {@link int}in the series of UID for the
	 *         AbstractPublisher derived classes
	 * @return
	 */
	protected static int getNewPubID() {
		return pubUIDs++;
	}

}
