

def parse_data(data):
	parsed_data = []
	for line in data:
		parsed = line.translate(None, '()".\'!?+-=\\:/_;%&$')
		#parsed = parsed.translate(None, ')')
		parsed = parsed.split(',')
		parsed_data.append(parsed)
	return parsed_data

def create_vocab(data):
	vocab = []
	for sentence in data:
		words = sentence[0].split(' ')	
		for word in words:
			#hanlde base case
			if not vocab:
				vocab.append([word,1])
			
			added = False
			for value in vocab:
				if word in value:
					value[1] += 1
					added = True

			if added == False:
				vocab.append([word,1])

	vocab.sort()
	return vocab

def vector_create(vocab):
	feature_vector = []
	#Feature vector is the length of vocab+1, where length + 1 is the classification
	for i in range(0, len(vocab)+1):
		feature_vector.append(0)
	return feature_vector

def output_preprocessed_set(vocab, data, file_name, is_training):
	feature_vectors = []
	f = open(file_name, 'w')
	for value in vocab:
		f.write(value[0] + ',')

	f.write('\n')

	for sentence in data:
		words = sentence[0].split(' ')
		#create the training set output
		output = vector_create(vocab)
		for word in words:
			for i in range(0, len(output)-1):
				#print(word, vocab[i][0])
				if vocab[i][0] == word:
					output[i] = 1
					#print(word)

		#If it's been classified, classify it in the output
		if is_training and len(sentence) == 2 and sentence[1] == '1':
			output[-1] = 1
		
		feature_vectors.append(output)
		f.write("%s\n" % output)
	f.close()

	return feature_vectors

def main():
	#Read in the training data
	train = open("training_text.txt").read().splitlines()
	data = parse_data(train)
	#Create the vocabulary from the training set
	vocab = create_vocab(data)
	train_vectors = output_preprocessed_set(vocab, data, "preprocessed_train.txt", True)

	#Read in the test data
	test = open("test_text.txt").read().splitlines()
	t_data = parse_data(test)
	test_vectors = output_preprocessed_set(vocab, t_data, "preprocessed_test.txt", False)

main()
