package orchestration;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import events.AbstractEvent;
import events.EventFactory;
import events.EventMessage;
import events.EventType;
import pubSubServer.AbstractChannel;
import pubSubServer.ChannelAccessControl;
import pubSubServer.ChannelDiscovery;
import pubSubServer.SubscriptionManager;
import publishers.AbstractPublisher;
import publishers.PublisherFactory;
import publishers.PublisherType;
import states.subscriber.StateName;
import strategies.publisher.StrategyName;
import subscribers.AbstractSubscriber;
import subscribers.SubscriberFactory;
import subscribers.SubscriberType;

public class Orchestration {

	public static void main(String[] args) {

		List<AbstractPublisher> listOfPublishers = new ArrayList<>();
		List<AbstractSubscriber> listOfSubscribers = new ArrayList<>();
		Orchestration testHarness = new Orchestration();
		try {
			listOfPublishers = testHarness.createPublishers();
			listOfSubscribers = testHarness.createSubscribers();

			List<AbstractChannel> channels = ChannelDiscovery.getInstance().listChannels();
			// For demonstration purposes only
			try {
				BufferedReader initialChannels = new BufferedReader(new FileReader(new File("Channels.chl")));
				List<String> channelList = new ArrayList<String>();
				String line = "";
				while ((line = initialChannels.readLine()) != null)
					channelList.add(line);
				int subscriberIndex = 0;
				for (AbstractSubscriber subscriber : listOfSubscribers) {
					subscriber.subscribe(channelList.get(subscriberIndex % channelList.size()));
					subscriberIndex++;
				}
				initialChannels.close();
			} catch (IOException ioe) {
				System.out.println("Loading Channels from file failed proceeding with random selection");
				for (AbstractSubscriber subscriber : listOfSubscribers) {
					int index = (int) Math.round((Math.random() * 10)) / 3;
					SubscriptionManager.getInstance().subscribe(channels.get(index).getChannelTopic(), subscriber);
				}
			}
			for (AbstractPublisher publisher : listOfPublishers) {
				publisher.publish();
			}

		} catch (IOException ioe) {
			System.out.println(ioe.getMessage());
			System.out.println("Will now terminate");
			return;
		}
		for (AbstractPublisher publisher : listOfPublishers) {
			publisher.publish();
		}

		// Scenario run through

		try {
			BufferedReader scenario = new BufferedReader(new FileReader(new File("Scenario.txt")));
			String line = "";
			String[] words;

			while ((line = scenario.readLine()) != null) {
				boolean found = false;
				words = line.split("\\W+");
				// Publisher block
				if (words[0].equals("PUB")) {
					AbstractEvent event;
					String type = words[2];
					int pubID = Integer.parseInt(words[1]);
					String eventMsgHeader = words[3];
					String eventMsgPayload = words[4];
					EventMessage message = new EventMessage(eventMsgHeader, eventMsgPayload);

					if (type.equals("TypeA")) {
						event = EventFactory.createEvent(EventType.TypeA, pubID, message);
					} else if (type.equals("TypeB")) {
						event = EventFactory.createEvent(EventType.TypeB, pubID, message);
					} else if (type.equals("TypeC")) {
						event = EventFactory.createEvent(EventType.TypeC, pubID, message);
					} else {
						event = EventFactory.createEvent(EventType.TypeA, pubID, message);
					}

					for (int i = 0; i < listOfPublishers.size(); i++) {
						if ((listOfPublishers.get(i).getID()) == pubID) {
							listOfPublishers.get(i).publish(event);
							found = true;
							break;
						}
					}
					// If particular pub not found, we will create a new pub and publish the event
					// for them
					if (!found) {
						AbstractPublisher newPub = PublisherFactory.createPublisher(PublisherType.alphaPub,
								StrategyName.AStrategy);
						listOfPublishers.add(newPub);
						newPub.publish(event);
					}
				}
				// Subscriber block
				else if (words[0].equals("SUB")) {
					int subID = Integer.parseInt(words[1]);
					for (int i = 0; i < listOfSubscribers.size(); i++) {
						if ((listOfSubscribers.get(i).getID()) == subID) {
							listOfSubscribers.get(i).subscribe(words[2]);
							found = true;
							break;
						}
						// If particular sub not found, we will create a new sub and subscriber to the
						// channel for them
						if (!found) {
							AbstractSubscriber newSub = SubscriberFactory.createSubscriber(SubscriberType.alpha,
									StateName.defaultState);
							listOfSubscribers.add(newSub);
							newSub.subscribe(words[2]);
						}
					}
				}
				// Block block
				else if (words[0].equals("BLOCK")) {
					int subID = Integer.parseInt(words[1]);
					for (int i = 0; i < listOfSubscribers.size(); i++) {
						if ((listOfSubscribers.get(i).getID()) == subID) {
							ChannelAccessControl.getInstance().blockSubcriber(listOfSubscribers.get(i), words[2]);
							break;
						}
					}

				}
				// Unblock block
				else if (words[0].equals("UNBLOCK")) {
					int subID = Integer.parseInt(words[1]);
					for (int i = 0; i < listOfSubscribers.size(); i++) {
						if ((listOfSubscribers.get(i).getID()) == subID) {
							ChannelAccessControl.getInstance().unBlockSubscriber(listOfSubscribers.get(i), words[2]);
							break;
						}
					}
				}
				// Unsubscribe block
				else if (words[0].equals("UNSUB")) {
					int subID = Integer.parseInt(words[1]);

					for (int i = 0; i < listOfSubscribers.size(); i++) {
						if ((listOfSubscribers.get(i).getID()) == subID) {
							listOfSubscribers.get(i).unsubscribe(words[2]);
							break;
						}
					}
				}
			}
			scenario.close();
		} catch (IOException ioe) {
			System.out.println("Error loading file!");
		}

	}

	private List<AbstractPublisher> createPublishers() throws IOException {
		List<AbstractPublisher> listOfPublishers = new ArrayList<>();
		AbstractPublisher newPub;
		BufferedReader StrategyBufferedReader = new BufferedReader(new FileReader(new File("Strategies.str")));
		while (StrategyBufferedReader.ready()) {
			String PublisherConfigLine = StrategyBufferedReader.readLine();
			String[] PublisherConfigArray = PublisherConfigLine.split("\t");
			int[] PublisherConfigIntArray = new int[2];
			for (int i = 0; i < PublisherConfigArray.length; i++)
				PublisherConfigIntArray[i] = Integer.parseInt(PublisherConfigArray[i]);
			newPub = PublisherFactory.createPublisher(PublisherType.values()[PublisherConfigIntArray[0]],
					StrategyName.values()[PublisherConfigIntArray[1]]);
			listOfPublishers.add(newPub);

		}
		StrategyBufferedReader.close();
		return listOfPublishers;
	}

	private List<AbstractSubscriber> createSubscribers() throws IOException {
		List<AbstractSubscriber> listOfSubscribers = new ArrayList<>();
		AbstractSubscriber newSub;
		BufferedReader StateBufferedReader = new BufferedReader(new FileReader(new File("States.sts")));
		while (StateBufferedReader.ready()) {
			String StateConfigLine = StateBufferedReader.readLine();
			String[] StateConfigArray = StateConfigLine.split("\t");
			int[] StateConfigIntArray = new int[2];
			for (int i = 0; i < StateConfigArray.length; i++)
				StateConfigIntArray[i] = Integer.parseInt(StateConfigArray[i]);
			newSub = SubscriberFactory.createSubscriber(SubscriberType.values()[StateConfigIntArray[0]],
					StateName.values()[StateConfigIntArray[1]]);
			listOfSubscribers.add(newSub);
		}
		StateBufferedReader.close();
		return listOfSubscribers;
	}

}
