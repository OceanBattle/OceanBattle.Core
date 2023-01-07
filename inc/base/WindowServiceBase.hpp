#ifndef __WINDOWSERVICEBASE__
#define __WINDOWSERVICEBASE__

// Part TOP layer.
// Service used by Visual and Interactive block.
// Both blocks are using same instance of this service.
// It's used to implement window related details.
// Interactive block reads from it events, Visual sends here render commands.
//
class WindowServiceBase {
	public:
		// - - - - Starting and Terminating - - - -

		// Starts window.
		// Must be used before linking with Visual/Interactive block.
		virtual void StartWindow(void * data) = 0;

		// Destoys window. Use at the end of program.
		virtual void Terminate() = 0;

		// - - - - Other functions. - - - -

		// Receives data from Visual block.
		// Data is saved o internall buffer.
		virtual void ReceiveVisual(void * data) = 0;
		
		// Draws data related to mouse position for example hover. 
		virtual void Update() = 0;

		// Poll window events.
		virtual void PollEvents(void * data) = 0;

		// Sets local map for rendering
		virtual void SetLocalMap(void * map) = 0;

		// Sets server map for rendering
		virtual void SetServerMap(void * map) = 0;

		// Checks if window is open.
		virtual bool IsOpen() = 0;


};

#endif
