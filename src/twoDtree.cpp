#include "include/twoDtree.h"
#include "math.h"

twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL) {
	}

twoDtree::~twoDtree() {
	clear();
}

twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

twoDtree & twoDtree::operator=(const twoDtree & rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn) { 
	
	pair<int,int> ul;
	pair<int,int> lr;
	
	ul.first = 0;
	ul.second = 0;
	
	lr.first = imIn.width() - 1;
	lr.second = imIn.height() - 1;
	
	stats imgStats = stats(imIn);
	this->width = lr.first + 1;
	this->height = lr.second + 1;
	this->root = buildTree(imgStats, ul, lr);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {

	Node* create = new Node(ul, lr, s.getAvg(ul,lr));
	
	if (ul != lr) {
		long minScore = LONG_MAX;
		long score;
		
		pair<int, int> nextLR = lr;
		pair<int, int> secondUL = ul;
		pair<int, int> splitLR = lr;
		pair<int, int> splitUL = ul;
		
		nextLR.second = lr.second;
		secondUL.second = ul.second;
		
		for (int i = ul.first; i < lr.first; i++) {
			nextLR.first = i;
			secondUL.first = i + 1;
			score = s.getScore(ul, nextLR) + s.getScore(secondUL, lr);
			
			if (score <= minScore) {
				minScore = score;
				splitLR = nextLR;
				splitUL = secondUL;
			}
		}
		
		nextLR.first = lr.first;
		secondUL.first = ul.first;
		
		for (int i = ul.second; i < lr.second; i++) {
			nextLR.second = i;
			secondUL.second = i + 1;
			score = s.getScore(ul, nextLR) + s.getScore(secondUL, lr);
			
			if (score <= minScore) {
				minScore = score;
				splitLR = nextLR;
				splitUL = secondUL;
			}
		}
		
		create->left = buildTree(s, ul, splitLR);
		create->right = buildTree(s, splitUL, lr);
	}

	return create;
}

PNG twoDtree::render() {
	int width = root->lowRight.first + 1;
	int height = root->lowRight.second + 1;

	PNG img = PNG(width, height);
	changeLeafColour(root, img);
	
	return img;
}

void twoDtree::changeLeafColour(Node* root, PNG &img) {
	if (root->left == NULL && root->right == NULL) {
		for (int x = root->upLeft.first; x <= root->lowRight.first; x++) {
			for (int y = root->upLeft.second; y <= root->lowRight.second; y++) {
				*img.getPixel(x, y) = root->avg;
			}
		}
	} else {
		changeLeafColour(root->left, img);
		changeLeafColour(root->right, img);	
	}
	return;
}

void twoDtree::prune(double pct, int tol) {
	toPrune(root, pct, tol);
}

void twoDtree::toPrune(Node* &node, double pct, int tol) {
	if (node != NULL) {
		double withinTol = 0;
		double totalNodes = 0;
		calculateDistance(node, node, withinTol, totalNodes, tol);

		if (withinTol / totalNodes >= pct) {
			deleteTree(node->right);
			deleteTree(node->left);
		} else {
			toPrune(node->right, pct, tol);
			toPrune(node->left, pct, tol);
		}
	}
}

void twoDtree::calculateDistance(Node* &subRoot, Node* &child, double &withinTol, double &totalNodes, int tol) {
	if (child != NULL) {
		if (child-> right == NULL && child->left == NULL) {
			int red = pow(child->avg.r - subRoot->avg.r, 2);
			int green = pow(child->avg.g - subRoot->avg.g, 2);
			int blue = pow(child->avg.b - subRoot->avg.b, 2);

			if (red + green + blue <= tol) {
				withinTol++;
			}
			totalNodes++;
		}

		calculateDistance(subRoot, child->right, withinTol, totalNodes, tol);
		calculateDistance(subRoot, child->left, withinTol, totalNodes, tol);
	}
}

void twoDtree::clear() {
	deleteTree(root);
	root = NULL;
}

void twoDtree::deleteTree(Node* &rootD) {
	if (rootD != NULL) {
		deleteTree(rootD->left);
		deleteTree(rootD->right);

		free(rootD);
		rootD = NULL;
	}
}

void twoDtree::copy(const twoDtree & orig){
	this->root = copyTree(orig.root);
}

twoDtree::Node* twoDtree::copyTree(Node* other) {
	if (other != NULL) {
		Node* toCopy = new Node(other->upLeft,other->lowRight,other->avg);
		toCopy->left = copyTree(other->left);
		toCopy->right = copyTree(other->right);
	
		return toCopy;
	} else {
		return NULL;
	}
}