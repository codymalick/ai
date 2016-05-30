#!/usr/bin/env python2

# CS 331, Programming Assignment 3
# Group: Cody Malick, Andrew Tolvstad


def parse_data(data):
	parsed_data = []
	for line in data:
		parsed = line.translate(None, '()".\'!?+-=\\:/_;%&$')
		parsed = parsed.split(',')
		parsed_data.append(parsed)
	return parsed_data

def create_vocab(data):
	vocab = []
	for sentence in data:
		words = sentence[0].split(' ')	
		for word in words:
			# Hanlde base case
			if not vocab:
				if len(sentence) == 2 and sentence[1] == '1':
					# Vocab[word, count, positive sarcasm count]
					vocab.append([word,1,1])
					break
				else:
					vocab.append([word,1,0])
					break
			
			added = False
			for value in vocab:
				if word in value:
					value[1] += 1
					if len(sentence) == 2 and sentence[1] == '1':
						value[2] += 1
					added = True

			if added == False:
				if len(sentence) == 2 and sentence[1] == '1':
					vocab.append([word,1,1])
				else:
					vocab.append([word,1,0])

	vocab.sort()
	return vocab

# Creates an empty feature vector based off of vocabulary
def vector_create(vocab):
	feature_vector = []
	# Feature vector is the length of vocab+1, where length + 1 is the classification
	for i in range(0, len(vocab)+1):
		feature_vector.append(0)
	return feature_vector

# Outputs the preprocessed set
def output_preprocessed_set(vocab, data, file_name, is_training):
	feature_vectors = []
	f = open(file_name, 'w')
	for value in vocab:
		f.write(value[0] + ',')

	f.write('\n')

	for sentence in data:
		words = sentence[0].split(' ')
		# Create the training set output
		output = vector_create(vocab)
		for word in words:
			for i in range(0, len(output)-1):
				if vocab[i][0] == word:
					output[i] = 1

		# If it's been classified, classify it in the output
		if is_training and len(sentence) == 2 and sentence[1] == '1':
			output[-1] = 1
		
		feature_vectors.append(output)
		f.write("%s\n" % output)
	f.close()

	return feature_vectors

# Trains the classifiers on the given set of values
def training(vocab, vectors):
	probabilities = []

	for i in range(0, len(vocab)):
		# Add positive probability and negative probability
		word_p = [float(vocab[i][2])/float(vocab[i][1]), float(vocab[i][1]-vocab[i][2])/float(vocab[i][1])]
		probabilities.append(word_p)
	
	total_positive = 0
	total_negative = 0
	for sentence in vectors:
		if sentence[-1] == 1:
			total_positive += 1
		else:
			total_negative += 1

	probabilities.append(total_positive)
	probabilities.append(total_negative)
	
	return probabilities

def classify(probabilities, vectors):
	# Get total counts of positive and negative classifications
	result = []
	total_positive = probabilities[-2]
	total_negative = probabilities[-1]
	for i in range(0, len(vectors)):
		positive_p = 1
		negative_p = 1
		# If this sentence is classified as satirical
		# Iterate over every word in the array
		for j in range(0, len(vectors[i])-1):
			# Check over each word, see if it is used
			if vectors[i][j] == 1:
				# If it is used, then calculate the probability, count over the total positive count
				positive_p *= probabilities[j][0]
			else:
				# Else we want to add the probability to the negative column
				negative_p *= probabilities[j][1]

		# Now multiply combined probabilities times the total number of positive classifications, and negative classifications
		positive_p *= float(total_positive)/float(total_positive + total_negative)
		negative_p *= float(total_negative)/float(total_positive + total_negative)

		# Round to readable format
		if(positive_p > negative_p):
			result.append(1)
		else:
			result.append(0)
	return result

# Counts results against actual sarcasm		
def real_count(vectors, calculated, output_file):
	correct = 0
	incorrect = 0
	answers = []
	for i in range(0, len(vectors)):
		if vectors[i][-1] == 1:
			answers.append(1)
		else:
			answers.append(0)
	
	for i in range(0, len(calculated)):
		if calculated[i] == answers[i]:
			correct += 1
		else:
			incorrect += 1
	output_file.write("Correct: " + str(correct) + "\n")
	output_file.write("Incorrect: " + str(incorrect) + "\n")
	output_file.write("Accuracy: " + str(float(correct)/float(incorrect+correct)) + "\n" )

def main():
	output_file = open('results.txt', 'w')
	# Read in the training data
	train = open("training_text.txt").read().splitlines()
	data = parse_data(train)
	# Create the vocabulary from the training set
	vocab = create_vocab(data)
	train_vectors = output_preprocessed_set(vocab, data, "preprocessed_train.txt", True)

	# Read in the test data
	test = open("test_text.txt").read().splitlines()
	t_data = parse_data(test)
	test_vectors = output_preprocessed_set(vocab, t_data, "preprocessed_test.txt", False)

	# Train the classifier
	classifier = training(vocab, train_vectors)

	# Training data results
	train_results = classify(classifier, train_vectors)
	
	# Print results

	output_file.write("Training : \"training_text.txt\" - Testing: \"training_text.txt\"\n")
	real_count(train_vectors, train_results, output_file)

	# Test data results
	test_results = classify(classifier, test_vectors)
	
	# Print results
	output_file.write("Training: File \"training_text.txt\" - Testing: \"test_text.txt\"\n")
	real_count(test_vectors, test_results, output_file)
	output_file.close()

main()
